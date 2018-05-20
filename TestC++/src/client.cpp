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
#include <string.h>

#define MAX_EVENTS 10

int main() {
	// socket
	struct sockaddr_in servaddr;
	short port = 9527;
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	servaddr.sin_port = htons(port);

	if (connect(sockfd, (sockaddr *) &servaddr, sizeof(sockaddr_in)) < 0) {
		perror("connect fail");
		exit(EXIT_FAILURE);
	}

	const char* buf = "daiyudong";
	const char* buf1 = "aaaaafffff";
//	for (;;) {
	int len = (int) write(sockfd, buf, strlen(buf));
	int len1 = (int) write(sockfd, buf1, strlen(buf1));
	if (len > 0) {
		printf("write len=%d,len1=%d\n", len, len1);
	}
	sleep(1);
//	}
}
