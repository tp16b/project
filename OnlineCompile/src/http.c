#include "http.h"
#include "error_respond.h"

#include "common.h"

enum { BUFF_SIZE=1024*4};

int RespondResouse(int sock, char* path, ssize_t size)/*{{{*/
{
	int ret = 200;
	char line[MAX];

	int open_fd = open(path, O_RDONLY);
	if( open_fd < 0){
		printf( "open failed\n");
		ret = 400;
	}else{ 
		sprintf( line, "HTTP/1.0 200 OK\r\n" ) ;
		send(sock, line, strlen(line), 0); //状态行 

		char* p = path + strlen( path)-1;
		while( *p != '.') --p;
		if( strcmp(p, ".css") == 0){ 
			sprintf(line, "Content-Type: text/css;charset=utf-8\r\n");
		}else if( strcmp(p, ".js") == 0){ 
			sprintf(line, "Content-Type: application/x-javascript\r\n");
		}else{ 
			//sprintf(line, "Content-Type: text/html;application/x-csi;application/x-jpg\r\n");
			sprintf(line, "Content-Type: text/html\r\n");
		}
		send( sock, line, strlen( line), 0);
		sprintf(line, "Content-Lenth: %d\r\n", size);
		send( sock, line, strlen(line), 0);
		send( sock, "\r\n" , 2, 0) ;  //空行

		if(sendfile(sock, open_fd, NULL, size)  < 0){ //正文 
			//可能是sock关闭了
			perror( "sendfile failed\n");
			ret  = 500;
		} 
	} 
	close( open_fd);
	return ret;
}/*}}}*/
static ssize_t getLine(int sock, char* line, int len) /*{{{*/
{ 
	assert( line && len> 0);
	char ch ='a';
	int i =0;
	//\n   \r  \r\n  =>  '\n'
	while( i< len && ch != '\n'){ 
		if(recv(sock, &ch, 1, 0) > 0){
			if(ch == '\r'){						//MSG_PEEK 窥探读取下一个字符
				if(recv(sock, &ch, 1, MSG_PEEK)>0 && ch == '\n')//是\n,读走 
					recv( sock, &ch, 1, 0);//进程阻塞的从sock读数据
				else  ch = '\n';
			}
			line[ i++] = ch;
		}else break;
	}
	line[i] = '\0';
	return i;
}/*}}}*/

/* BUG  
 * 由于是getLine为非阻塞的读取内容,如果客户端没有输入空行
 * 将在此死循环,同时将请求报文正文读走，导致cgi无法继续工作*/
static ssize_t clear_head(int sock)// 
{/*{{{*/ 
	ssize_t size =-1;
	char line[MAX];
	ssize_t count = 0;
	do{ 
		/* 简单处理： 计数超过10000，认为客户未键入空行*/
	//	if( count > 200000){ 
	//		break;
	//	}
		size = getLine(sock, line, MAX);
		//printf( " 此句话如果连续出现> 1000，说明没读到空行, 死循环\n");
		++count;
	}while(size != 1 || strcmp(line, "\n") != 0);
	
	return size; 
}/*}}}*/

int ExecCgi(int sock, const char* method, char* path, 
		const char* query_string) /*{{{*/
{ 
	printf( "############### come into cgi ##########\n");
	int ret_code = 200;
	int content_len = 0;
	////////////////////////////////////////////////////////
	//根据请求方法进行参数提取准备工作。若是GET方法,直接清理报头
	//若是POST方法，需要从请求报头中获取content-length的长度，
	//便于后续从请求正文中提取参数。
	//后序增添其他请求方法...
	///////////////////////////////////////////////////////
	if(strcasecmp(method, "GET") == 0){ 
		clear_head( sock);

	}else if(strcasecmp(method, "POST") == 0){//POST   提取报头content-length字段大小 
		char buf[MAX];
		int size =-1;
		do{ 
			size = getLine(sock, buf, sizeof(buf)-1);
			printf( "size=%d, buf=%s\n",size, buf);
			if(size>0 && strncasecmp(buf, "Content-Length: ", 16)==0)
				content_len = atoi(buf+16);
		}while(size!= 1);	
		printf( "content-length=%d\n", content_len);
		if(content_len <= 0){ 
			printf( "POST 方法请求报文中 content_len <=0\n");
			ret_code = 403;
		}
	}else{ 
	}
	//准备就绪，下面开始处理参数
	int input[2];  pipe(input);
	int output[2];  pipe(output);

	int pid = fork();
	if( pid == 0){ 
		//#########  child #############
		//1. 操作管道
		close( input[ 1]);
		close( output[0]);
		dup2( input[0], 0);
		dup2( output[1], 1);

		//2. 将参数导入环境变量
		char method_env[MAX>>1]; 
		char query_string_env[MAX>>1]; 
		char content_len_env[MAX>>1]; 
		sprintf(method_env, "METHOD=%s", method);	
		putenv(method_env);
		//a) GET
		if( strcasecmp(method, "GET")== 0){ 
			sprintf(query_string_env, "QUERY_STRING=%s", query_string);
			putenv(query_string_env);
		//b) POST
		}else{ 
			sprintf(content_len_env, "CONTENT_LEN=%d", content_len);
			putenv(content_len_env);
		}

		//3. !!!程序替换
		if(strcasecmp(path, "wwwroot/online_tools/Compile/run.sh") == 0){ 
			char* argv[] = {"/bin/bash","wwwroot/online_tools/Compile/run.sh", NULL};
			execvp("/bin/bash", argv); 
		}else{ 
			execl(path, path, NULL);
		}
		perror("execvp");exit( 1);

	}else if(pid > 0){ 
		//######### parent #########
		//1. 将output管道中的数据发送到sock，传到浏览器. 先处理管道
		close(input[0]);
		close(output[1]);

		char buff[BUFF_SIZE>>1] = { 0};
		//2. 针对请求方法进行相应处理，GET方法直接通过
		//query_string获得参数，若是POST方法，继续从sock获取数据，
		//提取请求正文中的参数;将参数送至input管道
		if(strcasecmp(method, "POST")== 0){ 
			recv(sock, buff, content_len, 0);  //recv ?
			write(input[1], buff, content_len);	
		}

		//3. 构造响应报文返回到浏览器
		//a) 报头进行response ：status+ head + \r\n + content
		const char* status = "HTTP/1.1 200 OK\r\n";
		const char* content_type= "Content-Type: text/html\r\n";
		send(sock, status, strlen(status), 0 );
		send(sock, content_type, strlen( content_type), 0 );
		send(sock, "\r\n", 2, 0 );

		char send_buf[BUFF_SIZE] = { 0};
		//char encode_buf[BUFF_SIZE] = { 0};
		ssize_t r=0, total=0;
		//b) 发送正文从output管道获取数据处理结果，通过sock，送至浏览器
		while((r=read(output[0], send_buf, BUFF_SIZE))  >0){ 
			total += r;
			printf( "%s", send_buf);
			//int encode_len = URLEncode(send_buf, r, encode_buf, BUFF_SIZE);
			send(sock, send_buf, r, 0);
			memset(send_buf, 0x00, BUFF_SIZE);
		//	memset(encode_buf, 0x00, BUFF_SIZE);
		}    
		printf( "send success... total_len=%d\n", total);
		waitpid(pid, NULL, 0);
		close(input[1]);
		close(output[0]);
	}else{ 
		ret_code= 503;
	}
	return ret_code;
}/*}}}*/

//static int URLEncode(const char* str, const int strSize, char* result, const int resultSize)

//分割字符串,获取请求方法、url、响应参数
int HandleRequestString(const char* line, ssize_t len, char* method, 
		char* url, char** pQuery)	/*{{{*/
{ 
	int cgi_flag = 0;
	int i = 0;
	int j =0;
	//1. 提取method
	while(j < len-1 && !isspace(line[j]) )  
		method[i++] = line[j++]; 
	method[i] = '\0';
	printf( "method:%s ", method);
	//j 指向第一个空格    如：GET /...
	while(j< len-1 && isspace(line[j]))
		j++;

	//2. 提取出url    
	i = 0;
	while( j< len-1 && !isspace(line[j]))  
		url[i++] = line[j++];
	url[i] = '\0';
	printf( "url:%s ", url);

	//3. url中定位query_string    xx/yy/zz?a=100&b=200
	if( strcasecmp("GET" ,method)  == 0){ 
		*pQuery= url;
		while(**pQuery!= '\0'  && **pQuery != '?') 
			(*pQuery)++;

		//如果存在'?' 表明有参数，使query_string指向参数处
		if(**pQuery == '?' ){ 
			**pQuery = '\0';
			(*pQuery) ++;
			cgi_flag = 1;
		} 
	} 
	return cgi_flag;
}/*}}}*/

 
int handleRequest(int con_fd, int epoll_fd)
{ /*{{{*/
	int ret_no = 0;
	int error_code = 200; //正常错误码 
	char line[MAX];
	char method[64];
	char url[MAX];
	char* query_string = NULL;
	int cgi_flag = 0;

	ssize_t line_size = getLine(con_fd, line, sizeof(line));
	if( line_size < 0){ 
		printf( "getline < 0\n");
		goto end;
	}
	if(line_size == 0){ 
		//读到文件尾端，  对端关闭了链接
		close(con_fd);
		epoll_ctl(epoll_fd, EPOLL_CTL_DEL, con_fd, NULL);
		printf("cli_%d say Bye!\n", con_fd);
		goto end;
	}
	cgi_flag = HandleRequestString(line, line_size, method, 
			url, &query_string);	

	char path[MAX];
	if(url[0] == '/' && strlen(url)<2){ 
		sprintf(url, "/%s", MAIN_PAGE);
	}
	sprintf(path,"%s%s", ROOT, url); //为web根目录添加访问目录	
	printf( "path: %s\n", path);
	//判定访问资源是否存在/*{{{*/
	struct stat st;
	if(stat(path, &st) < 0){ 
		printf( "stat failed\n");
		clear_head(con_fd);    //清理头
		error_code = 404;  //没有资源 
		goto end;
	}else{ 
		if((st.st_mode& S_IFMT)  == S_IFREG){//regular file? 
			//是否是具有可执行权限的二进制文件
			if( st.st_mode & S_IXUSR ||
				st.st_mode & S_IXGRP ||
				st.st_mode & S_IXOTH  )	
				cgi_flag = 1;
		}else if((st.st_mode & S_IFMT) == S_IFDIR ){  //direct?
		//	printf( "is ddddddddddddddddddddddddddddddddddddddddddddirect\n");
			//判断是否具有可读权限？没有跳转错误，有 响应相关页面
			if(0 == strncasecmp(path, "wwwroot/cgi_src", 15)){ 
				clear_head(con_fd);//清理头
				error_code = 403;
				goto end;
			} 
		}    
	}/*}}}*/
	//返回资源,服务Respond
	if(cgi_flag){ 
		error_code = ExecCgi(con_fd, method, path, query_string);
	}
	else{ 
		clear_head(con_fd);
		error_code = RespondResouse(con_fd, path, st.st_size);
	}
end:
	if(error_code != 200){ 
		printf( "error_code: %d\n", error_code);
		if(echo_error(con_fd, error_code) < 0){ 
			printf("echo_error faild...\n");
			ret_no = -1;
		}
	} 
	close(con_fd);
	return ret_no;
} /*}}}*/
