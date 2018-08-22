#include "http.h"
#define N 10

int startup(int port) /*{{{*/
{ 
	int sock = socket(AF_INET, SOCK_STREAM, 0);
	if( sock< 0){ 
		perror("socket"),exit(2);	
	}
	int opt =1;
	setsockopt(sock, SOL_SOCKET, SO_REUSEPORT, &opt, sizeof( opt) );

	struct sockaddr_in local;
	local.sin_family = AF_INET;
	local.sin_addr.s_addr = htonl(INADDR_ANY); 
	local.sin_port = htons(port);
	if( bind(sock, (struct sockaddr*)&local, sizeof(local))< 0 ){ 
		perror("bind"),exit( 3);
	}
	if( listen(sock, 5)< 0){ 
		perror("listen"),exit( 4);
	}
	return sock;
}/*}}}*/

int main(int argc, char* argv[ ] )
{ 
	if( argc != 2){ 
		printf( "Usage: command+ port\n");
		return 1;
	}
	int listen_sock = startup(atoi(argv[ 1]));

	int epoll_fd = epoll_create(N);
	struct epoll_event event;
	event.events = EPOLLIN;
	event.data.fd = listen_sock;
	epoll_ctl( epoll_fd, EPOLL_CTL_ADD, listen_sock, &event);

	while( 1){ 
		struct epoll_event event_list[N];

		int nfd = epoll_wait(epoll_fd, event_list, N, -1); 
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
				ev.events = EPOLLIN;
				if(epoll_ctl(epoll_fd, EPOLL_CTL_ADD, con_fd, &ev) < 0){ 
					perror("epoll_ctl"); continue;
				}
			}else{ 
				if(event_list[i].events & EPOLLIN){ 
				//con_fd 有读事件就绪，处理请求 
					int ret =handleRequest(event_list[i].data.fd, epoll_fd);
					if( ret < 0)  { perror("handleRequest"); continue;}
				} 
			}
		}
	}
	close( listen_sock);
	return 0;
}

