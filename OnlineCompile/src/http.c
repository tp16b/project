#include "http.h"
#include "error_respond.h"
#include "common.h"
#include "exec_cgi.h"

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
		sprintf(line, "Content-Lenth: %ld\r\n", size);
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

 
void* HandleRequest(void* arg)
{ /*{{{*/
	int con_fd = ((fds_t*)arg)->handlefd;
	int epoll_fd = ((fds_t*)arg)->epollfd;

	int cgi_flag=0, error_code=200; //正常错误码 
	char line[MAX];                 //暂存从内核缓存读取一行http报文
	char method[32];                //http请求方法
	char url[MAX];                  //url报文
	char path[MAX];					//存放路径
	char* query_string = NULL;

	ssize_t line_size = getLine(con_fd, line, sizeof(line));
	if( line_size < 0){ 
		printf( "getline < 0\n");
		goto end;
	}
	if(line_size == 0){ 
		//读到文件尾端，对端关闭了链接
		close(con_fd);
		epoll_ctl(epoll_fd, EPOLL_CTL_DEL, con_fd, NULL);
		printf("【cli_%d say Bye!】\n", con_fd);
		goto end;
	}
	cgi_flag = HandleRequestString(line, line_size, method,
			url, &query_string);	

	if(url[0] == '/' && strlen(url)<2){ 
		sprintf(url, "/%s", MAIN_PAGE);
	}
	sprintf(path, "%s%s", ROOT, url);      //为web根目录添加访问目录	
	printf( "path: %s\n", path);
	//判定访问资源是否存在
	struct stat st;
	if(stat(path, &st) < 0){ 
		printf( "stat failed\n");
		clear_head(con_fd);                 //没有资源 清理头
		error_code = 404;          
		goto end;

	}else{ //regular file?
		if((st.st_mode& S_IFMT)  == S_IFREG){ 
			//是否是具有可执行权限的二进制文件
			if( st.st_mode & S_IXUSR ||
				st.st_mode & S_IXGRP ||
				st.st_mode & S_IXOTH  )	
				cgi_flag = 1;
		}else if((st.st_mode & S_IFMT) == S_IFDIR ){  //direct?
			//判断是否具有可读权限？没有跳转错误，有 响应相关页面
			if(0 == strncasecmp(path, "wwwroot/cgi_src", 15)){ 
				clear_head(con_fd);//清理头
				error_code = 403;
				goto end;
			} 
		}    
	}
	//返回资源,服务Respond
	if(cgi_flag)  
		error_code = ExecCgi(con_fd, method, path, query_string);
	else{ 
		clear_head(con_fd);
		error_code = RespondResouse(con_fd, path, st.st_size);
	}
end:
	if(error_code != 200){ 
		printf( "error_code: %d\n", error_code);
		if(echo_error(con_fd, error_code) < 0){ 
			printf("echo_error faild...\n");
		}
	} 
	ResetOneshot(epoll_fd, con_fd);
	close(con_fd);  //?关闭
	return NULL;
} /*}}}*/
