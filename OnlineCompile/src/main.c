#include "http.h"
#define MAX_EVENTS 1000 

void ResetOneshot(int epollfd, int fd)  
{ 
	struct epoll_event event;
	event.data.fd = fd;
	event.events = EPOLLIN | EPOLLONESHOT;
	epoll_ctl(epollfd, EPOLL_CTL_MOD, fd, &event);
}

int startup(int port) /*{{{*/
{ 
	int sock = socket(AF_INET, SOCK_STREAM, 0);
	if( sock< 0){ 
		perror("socket"),exit(2);	
	}
	int opt =1;
	setsockopt(sock, SOL_SOCKET, SO_REUSEPORT, &opt, sizeof(opt));

	struct sockaddr_in local;
	local.sin_family = AF_INET;
	local.sin_addr.s_addr = htonl(INADDR_ANY); 
	local.sin_port = htons(port);
	if( bind(sock, (struct sockaddr*)&local, sizeof(local))< 0 ){ 
		perror("bind"),exit( 3);
	}
	if( listen(sock, 1000)< 0){ 
		perror("listen"),exit( 4);
	}
	return sock;
}/*}}}*/

int main(int argc, char* argv[ ] )
{ 
	if( argc != 2){ 
		printf( "Usage: server+ port\n");
		return 1;
	}
	int listen_sock = startup(atoi(argv[ 1]));

	int epoll_fd = epoll_create(5);
	struct epoll_event event;
	event.events = EPOLLIN;
	event.data.fd = listen_sock;
	epoll_ctl( epoll_fd, EPOLL_CTL_ADD, listen_sock, &event);

	while( 1){ 
		struct epoll_event event_list[MAX_EVENTS];

		int nfd = epoll_wait(epoll_fd, event_list, MAX_EVENTS, -1); 
		if( nfd < 0)	{perror("epoll_wait"); continue; }
		if( nfd == 0)	{perror("epoll timeout"); continue; }
	
		int i =0;
		for(; i< nfd; ++i ){ 
			if(event_list[i].data.fd == listen_sock){ 
				//处理连接   listen_sock上有新请求连接，读事件就绪
				int con_fd = accept(listen_sock, NULL, NULL); 
				if( con_fd< 0)	{printf("accept faild\n");continue;}

				printf( "got a new client!, cli_fd=%d\n", con_fd);
				//accept后con_fd添加进epoll
				struct epoll_event ev;
				ev.data.fd = con_fd;
				/*对每个非listen_sock的con_fd注册EPOLLONESHOT,只触发事件
				 * 就绪的con_fd一次，防止多个线程一起操作一个con_fd*/
				ev.events = EPOLLIN | EPOLLONESHOT;  

				if(epoll_ctl(epoll_fd, EPOLL_CTL_ADD, con_fd, &ev) < 0){ 
					perror("epoll_ctl"); continue;
				}
			}else{ 
				if(event_list[i].events & EPOLLIN){ 
				//con_fd 有读事件就绪，处理请求 
					//printf( "!!!!!!!!!!! once more !!!!!!!\n");
					fds_t fds_new_work;
					fds_new_work.epollfd = epoll_fd;
					fds_new_work.handlefd = event_list[i].data.fd;

					/*新启动一个工作线程为handlefd服务*/
					pthread_t tid;					
					pthread_create(&tid, NULL, HandleRequest, (void*)&fds_new_work);
					pthread_detach(tid);
				} 
			}
		}
	}
	printf( "【Fatal!  程序允许结束】\n");
	close( listen_sock);
	close( epoll_fd);
	return 0;
}

