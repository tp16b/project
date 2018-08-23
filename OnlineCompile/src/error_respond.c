#include "http.h"
#include "error_respond.h"

int send_error_page(int sock, const char* path, int error_code)
{ 
	int ret =0;
	int fd =open(path, O_RDONLY); 
	if( fd < 0)  { 	ret = -1;}

	char line[MAX];
	//http/1.1 xxx 描述
	//报头
	//\r\n
	//正文

	sprintf(line, "HTTP/1.0 %d Forbidden\r\n", error_code ) ;
	send(sock, line, strlen(line), 0);
	
	struct stat st;
	if(stat(path, &st) < 0) 
		ret = -1; 
	sprintf( line, "Content-Type: text/html\r\n") ;
	send(sock, line, strlen(line), 0);

	sprintf( line, "Content-Length: %ld\r\n", st.st_size) ;
	send(sock, line, strlen(line), 0);

	send( sock, "\r\n" , 2, 0) ;

	if(sendfile(sock, fd, NULL, st.st_size)  < 0) { 
		printf( "sendfile fail!！\n");
		ret  = -1; 
	}
	close(fd);
	return ret;
}
int echo_error(int sock, int error_code) 
{ 
	int ret = 0;
	char path[MAX>>1] = "wwwroot/html/";	
	switch(error_code){ 
		case 204:   //请求已处理,但资源为空
			strcat(path, "204.html");
			ret= send_error_page(sock, path, error_code);
			break;
		case 206:   //范围请求
			strcat(path, "206.html");
			ret= send_error_page(sock, path, error_code);
			break;
		case 301:   //永久重定向,url已经改动
			strcat(path, "301.html");
			ret= send_error_page(sock, path, error_code);
			break;
		case 302:   //临时重定向,url已经改动
			strcat(path, "302.html");
			ret= send_error_page(sock, path, error_code);
			break;
		case 307:   //临时重定向,url已经改动
			strcat(path, "307.html");
			ret= send_error_page(sock, path, error_code);
			break;
		case 400:  //客户端请求资源格式错误
			strcat(path, "400.html");
			ret= send_error_page(sock, path, error_code);
			break;
		case 403:   //拒绝客户端访问
			strcat(path, "403.html");
			printf( "----------> ready to 403.html\n");
			ret= send_error_page(sock, path, error_code);
			break;
		case 404:  //访问资源不存在
			strcat(path, "404.html");
			ret= send_error_page(sock, path, error_code);
			break;
		case 500: //系统内部错误
			strcat( path, "500.html");
			ret= send_error_page(sock, path, error_code);
			break;
		case 503: //系统（繁忙）
			strcat( path, "503.html");
			ret= send_error_page(sock, path, error_code);
			break;
		default:
			;
	} 
	return ret;
}

