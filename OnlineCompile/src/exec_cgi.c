/*************************************************************************
  > File Name: exec_cgi.c
  > Author: tp
  > Mail: 
  > Created Time: Thu 23 Aug 2018 06:44:18 PM CST
 ************************************************************************/

#include "exec_cgi.h"

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
		printf( "send success... total_len=%ld\n", total);
		waitpid(pid, NULL, 0);
		close(input[1]);
		close(output[0]);
	}else{ 
		ret_code= 503;
	}
	return ret_code;
}/*}}}*/


