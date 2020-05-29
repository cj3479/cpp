//
// Created by chengjian on 2020/1/28.
//
#include "TestModuleA.h"
#include  <stdio.h>
int aa;
static char *bb;
int cc=10;
static int *dd;
static int *ee=1;
//extern int ff;
int testabc();
int testFun(int a, int b){
    return a+b;
}

 void testA22(){
//    printf("%d",11);
}

//void testA() {
////    printf("%d", a);
//}
void testA(int a) {
    printf("%d", a);
}

int testFunLocal(int a, int b){
    printf("%d",aa);
    printf("%s",bb);
    printf("%d",cc);
    printf("%d",dd);
    printf("%d",ee);
    testabc();
    testA22();
    testA(10);
//    printf("%d",ff);
    return testFun(a,b);
}