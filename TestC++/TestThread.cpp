//
// Created by chengjian on 2020/1/30.
//
#include "TestThread.h"
#include <iostream>
#include <pthread.h>
#include <unistd.h>
#include <thread>

using namespace std;
void *start(void *data) {
    pthread_setname_np("dsdsd");
    cout << data << endl;
    printf("start  %s,pid=%d,ppid=%d,tid=%d\n", data, getpid(), getppid(),this_thread::get_id());
    sleep(1000);
}
void testCreateThread(){
    void *status_m;
    printf("testCreateThread pid=%d,ppid=%d,tid=%d\n",getpid(), getppid(),this_thread::get_id());
    pthread_t thread;
    //创建一个线程并自动执行
    int id = pthread_create(&thread, NULL, start, (void *) "this is thread");
    pthread_join(thread, &status_m);
};