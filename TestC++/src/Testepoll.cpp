#include <iostream>
#include <unistd.h>
#include <errno.h>
#include <sys/epoll.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>
using namespace std;

int main() {
	const int MAXEVENTS = 1024;                //最大事件数
	struct epoll_event events[MAXEVENTS];      //监听事件数组
	int ret, pid;
	int pipe_fd[2];
	int pipe_fd1[2];
	/**
	 * 调用pipe函数时在内核中开辟一块缓冲区（称为管道）用于通信，它有一个读端和一个写端，
	 * 然后通过fd参数传出给用户程序两个文件描述符，fd[0]指向管道的读端，fd[1]指向管道的写端（
	 * 很好记，就像0是标准输入1是标准输出一样）。
	 * 所以管道在用户程序看起来就像一个打开的文件，
	 * 通过read(fd[0])或者write(fd[1])向这个文件读写数据其实是在读写内核缓冲区。
	 * pipe函数调用成功返回0，调用失败返回-1。
	 */
	if ((ret = pipe(pipe_fd)) < 0) {
		cout << "create pipe fail:" << ret << ",errno:" << errno << endl;
		return -1;
	}
	if ((ret = pipe(pipe_fd1)) < 0) {
		cout << "create pipe1 fail:" << ret << ",errno:" << errno << endl;
		return -1;
	}
	struct epoll_event ev, ev1;                     //事件临时变量
	ev.data.fd = pipe_fd[0];        //设置监听文件描述符
	ev.events = /*EPOLLET | */EPOLLIN;    //设置要处理的事件类型
	ev1.events = /*EPOLLET | */EPOLLIN;    //设置要处理的事件类型
	ev1.data.fd = pipe_fd1[0];    //设置要处理的事件类型
	int epfd = epoll_create(MAXEVENTS);
	ret = epoll_ctl(epfd, EPOLL_CTL_ADD, pipe_fd[0], &ev);
	ret = epoll_ctl(epfd, EPOLL_CTL_ADD, pipe_fd1[0], &ev1);
	if (ret != 0) {
		cout << "epoll_ctl fail:" << ret << ",errno:" << errno << endl;
		close(pipe_fd[0]);
		close(pipe_fd[1]);
		close(epfd);
		return -1;
	}
	int fd[] = { pipe_fd[0], pipe_fd1[0] };
	printf("pipe_fd[0] is %d,fd[0]=%d,pipe_fd[1] is %d,fd[1]=%d\n", pipe_fd[0],
			fd[0], pipe_fd1[0], fd[1]);
	if ((pid = fork()) > 0) {
		for (;;) {
			sleep(2);
			int count = epoll_wait(epfd, events, MAXEVENTS, -1);
			printf("count is %d\n", count);
			char r_buf[100];
			for (int i = 0; i < count; i++) {
				printf("events[i].events is %d,fd[i]=%d,events[i].data.fd=%d\n",
						events[i].events, fd[i], events[i].data.fd);
				if ((events[i].data.fd == fd[i])
						&& (events[i].events & EPOLLIN)) {
					int r_num = read(fd[i], r_buf, 100);
					printf(
							"read num is %d bytes data from the pipe,value is %d \n",
							r_num, atoi(r_buf));
				}
			}
		}

		close(pipe_fd[1]);
		close(pipe_fd[0]);
		close(epfd);
		cout << "parent close read fd[0],wirte fd[1] and epfd over" << endl;

	} else if (pid == 0) {
		close(pipe_fd[0]);    //read
		cout << "sub close read fd[0] over,sub does't read" << endl;
		char w_buf[100];
		strcpy(w_buf, "1234");
		//you can remove this line for learn
		if (write(pipe_fd[1], w_buf, 5) != -1) {
			printf("sub write over \n");
		}
		sleep(1);
		if (write(pipe_fd1[1], w_buf, 5) != -1) {
			printf("sub write over \n");
		}
		close(pipe_fd[1]);    //write
		printf("sub close write fd[1] over \n");

	}

	return 0;
}

