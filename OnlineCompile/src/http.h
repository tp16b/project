#ifndef __HTTP_H__
#define __HTTP_H__


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>

#include <arpa/inet.h>
#include <netinet/in.h>

#include <sys/socket.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/sendfile.h>
#include <sys/epoll.h>

#include <fcntl.h>
#include <pthread.h>

#define ROOT "wwwroot"
#define MAIN_PAGE "index.html"

enum { MAX=1024};
typedef struct fds{ 
	int epollfd;
	int handlefd;
}fds_t;

static ssize_t getLine(int sock, char* line, int len) { 
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
}

static ssize_t clear_head(int sock){ 
	ssize_t size =-1;
	char line[MAX];
	ssize_t count = 0;
	do{ 
		size = getLine(sock, line, MAX);
		++count;
	}while(size != 1 || strcmp(line, "\n") != 0);
	
	return size; 
}
void ResetOneshot(int epollfd, int fd); 
void* HandleRequest(void* arg);

#endif   //__HTTP_H__
