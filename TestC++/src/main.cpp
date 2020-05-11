#include <iostream>
#include <zconf.h>
#include <sys/syscall.h>
#define __NR_gettid 186
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
using namespace std;


//extern void testAA();

 void *threadwrite(void *data) {
     printf("sub thread start\n");
     pthread_mutex_lock((pthread_mutex_t *)data);
     sleep(4);
     pid_t pid = fork();
     std::cout << "sub thread start pid=" << pid << "  getPid=" << getpid() <<" sub thread="<<pthread_self()<< std::endl;
     if (pid == 0) {
         int j;
         for (j = 0; j < 1; j++) {
             printf("child: %d pid=%d,ppid=%d,aa=%d\n", j, getpid(), getppid(), 11);
//            sleep(1);
         }
     } else if (pid > 0) {
         int i;
         for (i = 0; i < 1; i++) {
             printf("parent: %d pid=%d,ppid=%d\n", i, getpid(), getppid());
//            sleep(1);
         }
     } else {
//         fprintf(stderr, "can't fork ,error %d\n", errno);
//         exit(1);
     }
     std::cout << "sub thread end pid=" << pid << "  getPid=" << getpid() <<" sub thread="<<pthread_self()<< std::endl;
     pthread_mutex_unlock((pthread_mutex_t *)data);
 }
int main() {
    int aa = 10;
    std::cout << "Hello, World!" << std::endl;
//    testAA();
    pthread_t tid = pthread_self();
    std::cout << "Hello, World pid=" << getpid() <<"  tid="<<tid<< std::endl;
    pid_t pid = getpid();
    pthread_t thread;
    pthread_mutex_t pLock;
    pthread_mutex_init(&pLock, NULL);
    //创建一个线程并自动执行
    int id = pthread_create(&thread, NULL, threadwrite, &pLock);
    printf("thread =%p\n",thread);
    sleep(1);
    pthread_mutex_lock(&pLock);
    pthread_mutex_unlock(&pLock);
//    pid_t pid = fork();
//    std::cout << "Hello, World111 pid=" << pid << "  getPid=" << getpid() << std::endl;
//    if (pid == 0) {
//        int j;
//        for (j = 0; j < 1; j++) {
//            printf("child: %d pid=%d,ppid=%d,aa=%d\n", j, getpid(), getppid(), aa);
////            sleep(1);
//        }
//    } else if (pid > 0) {
//        int i;
//        for (i = 0; i < 1; i++) {
//            printf("parent: %d pid=%d,ppid=%d\n", i, getpid(), getppid());
////            sleep(1);
//        }
//    } else {
//        fprintf(stderr, "can't fork ,error %d\n", errno);
//        exit(1);
//    }
//    printf("This is the end !");
    printf("main thread end\n");
    return 0;
}