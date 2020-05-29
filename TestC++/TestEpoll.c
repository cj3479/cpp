////
//// Created by chengjian on 2020/1/30.
////
//
//#include "TestEpoll.h"
//#include <iostream>
//#include <sys/socket.h>
//#include <sys/epoll.h>
//#include <netinet/in.h>
//#include <arpa/inet.h>
//#include <fcntl.h>
//#include <unistd.h>
//#include <stdio.h>
//#include <errno.h>
//
//using namespace std;
//
//int epollListen() {
//    int ret = 0;
//    int pipe_fd[2];
//    int pipe_fd1[2];
//    /**
//     * 调用pipe函数时在内核中开辟一块缓冲区（称为管道）用于通信，它有一个读端和一个写端，
//     * 然后通过fd参数传出给用户程序两个文件描述符，fd[0]指向管道的读端，fd[1]指向管道的写端（
//     * 很好记，就像0是标准输入1是标准输出一样）。
//     * 所以管道在用户程序看起来就像一个打开的文件，
//     * 通过read(fd[0])或者write(fd[1])向这个文件读写数据其实是在读写内核缓冲区。
//     * pipe函数调用成功返回0，调用失败返回-1。
//     */
//    if ((ret = pipe(pipe_fd)) < 0) {
//        cout << "create pipe fail:" << ret << ",errno:" << errno << endl;
//        return -1;
//    }
//    if ((ret = pipe(pipe_fd1)) < 0) {
//        cout << "create pipe1 fail:" << ret << ",errno:" << errno << endl;
//        return -1;
//    }
//    struct epoll_event ev, ev1;                     //事件临时变量
////	ev.data.fd = pipe_fd[0];        //设置监听文件描述符
//    ev.events = EPOLLET | EPOLLIN;    //设置要处理的事件类型
//    ev1.events = EPOLLET | EPOLLIN;    //设置要处理的事件类型
//    int epfd = epoll_create(MAXEVENTS);
//    ret = epoll_ctl(epfd, EPOLL_CTL_ADD, pipe_fd[0], &ev);
//    ret = epoll_ctl(epfd, EPOLL_CTL_ADD, pipe_fd1[0], &ev1);
//}
