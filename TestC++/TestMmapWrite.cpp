//
// Created by chengjian on 2020/2/7.
//

#include "TestMmapWrite.h"
#include <sys/mman.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

typedef struct
{
    char name[32];
    int age;
} people;

void testMMapWrtire(){
    people* p_map;
    char temp = 'o';

    int fd = open("../../2.txt", O_CREAT|O_RDWR|O_TRUNC, 00777);
    if (-1 == fd)
    {
        printf("open file error = %s\n", strerror(errno));
        return ;
    }
//    sleep(5);
    ftruncate(fd, sizeof(people)*10);
    printf("initialize mmap start\n");
    p_map = (people*)mmap(NULL, sizeof(people)*10, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
    if (MAP_FAILED == p_map)
    {
        printf("mmap file error = %s\n", strerror(errno));
        return;
    }
    printf("initialize start\n");
    for(int i = 0; i < 10; i++)
    {
        memcpy( ( *(p_map+i) ).name, &temp, 1);
//        printf("copy name[0]=%c,name=%s\n", (*(p_map+i) ).name[0],(*(p_map+i) ).name);
        ( *(p_map+i) ).name[1] = 0;
        ( *(p_map+i) ).age = 20+i;
        temp += 1;
//        printf("copy name=%s,temp=%c\n", (*(p_map+i) ).name,temp);
    }
    printf("initialize over\n");

//    close(fd);
    munmap(p_map, sizeof(people)*5);
//    msync(p_map, sizeof(people)*10, MS_SYNC );
//    sleep(10);
//    msync(p_map, sizeof(people)*10, MS_SYNC );
    printf("umap ok \n");
}