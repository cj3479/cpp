//
// Created by chengjian on 2020/5/11.
//

#include "TestExternal.h"
#include "iostream"
using namespace std;
int a=20;
int testAA(){
    printf("testAA");
    return 1;
}
void testPointer(int *p) {
    (*p) = (*p) + 10;
}