#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/epoll.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#define MAX_EVENTS 10
//参考https://blog.csdn.net/daiyudong2020/article/details/50449489
static void setnonblocking(int fd) {
	int flag = fcntl(fd, F_GETFL, 0);
	if (flag < 0) {
		perror("fcntl F_GETFL:");
		return;
	}
	if (fcntl(fd, F_SETFL, flag | O_NONBLOCK) < 0) {
		perror("fcntl F_SETFL:");
	}
}

static int epoll_add(int efd, int sock) {
	struct epoll_event ev;
	ev.events = EPOLLIN;
	ev.data.fd = sock;
	if (-1 == epoll_ctl(efd, EPOLL_CTL_ADD, sock, &ev)) {
		perror("epoll_ctl: sock");
		return 1;
	}
	return 0;
}

static void epoll_write(int efd, int sock, bool enable) {
	struct epoll_event ev;
	ev.events = EPOLLIN | (enable ? EPOLLOUT : 0);
	ev.data.fd = sock;
	epoll_ctl(efd, EPOLL_CTL_MOD, sock, &ev);
}

static void epoll_del(int efd, int sock) {
	epoll_ctl(efd, EPOLL_CTL_DEL, sock, NULL);
}

int main() {
	// socket
	int listenfd;
	struct sockaddr_in servaddr;
	short port = 9527;

	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(port);

	listenfd = socket(AF_INET, SOCK_STREAM, 0);
//	setnonblocking(listenfd);
	int res = bind(listenfd, (sockaddr *) &servaddr, sizeof(sockaddr_in));
	if (0 == res)
		printf("server bind success, 0.0.0.0:%d, addr=%d\n", port,
				servaddr.sin_addr.s_addr);
	else {
		perror("bind fail");
		exit(EXIT_FAILURE);
	}
	res = listen(listenfd, 100);
	if (0 == res)
		printf("server listen success\n");
	else {
		perror("listen fail");
		exit(EXIT_FAILURE);
	}

	// epoll
	struct epoll_event ev, events[MAX_EVENTS];
	int epollfd = epoll_create(10);
	if (-1 == epollfd) {
		perror("epoll_create fail");
		exit(EXIT_FAILURE);
	}

	ev.events = EPOLLIN; // LT
	ev.data.fd = listenfd;
	if (-1 == epoll_ctl(epollfd, EPOLL_CTL_ADD, listenfd, &ev)) {
		perror("epoll_ctl: listenfd fail");
		exit(EXIT_FAILURE);
	}
	printf("dgdsgdfsgdfgdfg\n");
	printf("dgdsgdfsgdfgdfg\n");
	int connfd = accept(listenfd, NULL, NULL);
	printf("connfd=%d\n", connfd);
//	char buf[100];
//	int r_num = read(connfd, buf, 100);
//	printf("read num is %d bytes data from the pipe,value is %d \n", r_num,
//			atoi(buf));
	for (;;) {
		int count = epoll_wait(epollfd, events, MAX_EVENTS, -1);
		printf("epoll_wait:%d\n", count);
		char r_buf[100];
		for (int i = 0; i < count; i++) {
			printf("events[i].data.fd is %d,events[0].events is %d, "
					"listenfd is %d\n", connfd, events[0].events, listenfd);
			int r_num = read(connfd, r_buf, 100);
			printf("read num is %d bytes data from the pipe,value is %s \n",
					r_num, r_buf);
		}
		//                }
		if (-1 == count) {
			perror("epoll_wait fail");
			exit(EXIT_FAILURE);
		}
//        for (int n = 0; n < nfds; ++n) {
//            if (events[n].data.fd == listenfd) {
//                int connfd = accept(listenfd, NULL, NULL);
//                if (-1 == connfd) {
//                    perror("accept fail");
//                    continue;
//                }
//                setnonblocking(connfd);
//                epoll_add(epollfd, connfd);
//                printf("connfd:%d\n", connfd);
//            }
//            else if (events[n].events & EPOLLIN) {
//                char buf[2] = {0};
//                int fd = events[n].data.fd;
//                size_t count = 1;
//                int len = (int)read(fd, buf, count);
//                if (len > 0) {
//                    printf("read len=%d buf=%s\n", len, buf);
//                    //epoll_write(epollfd, fd, false);
//                }
//                else if (len < 0) {
//                    switch(errno) {
//                    case EINTR:
//                    case EAGAIN:
//                        printf("try again\n");
//                        //epoll_write(epollfd, fd, false);
//                        break;
//                    default:
//                        epoll_del(epollfd, fd);
//                        close(fd);
//                        printf("game over\n");
//                    }
//                }
//                else if (len == 0) {
//                    epoll_del(epollfd, fd);
//                    close(fd);
//                    printf("game over\n");
//                }
//            }
//            else {
//                // pass
//            }
//        }
	}

}
