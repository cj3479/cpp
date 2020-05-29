//
// Created by chengjian on 2020/5/29.
//

#include <zconf.h>
#include <printf.h>

int main(int argc1, char* const argv1[]) {
    printf("before exc getpid=%d\n", getpid());
    sleep(20);
    printf("after exc getpid=%d\n", getpid());
}