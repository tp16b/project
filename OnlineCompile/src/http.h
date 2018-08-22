#ifndef __HTTP_H__
#define __HTTP_H__


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/epoll.h>
#include <fcntl.h>

#include <string.h>
#include <assert.h>

#define MAX 1024
#define ROOT "wwwroot"
#define MAIN_PAGE "index.html"


int handleRequest(int con_fd, int epoll_fd);
#endif   //__HTTP_H__
