//
// Created by chengjian on 2020/1/28.
//

#ifndef TESTC___TESTMODULEA_H
#define TESTC___TESTMODULEA_H

#ifdef __cplusplus //而这一部分就是告诉编译器，如果定义了__cplusplus(即如果是cpp文件，
extern "C"{ //因为cpp文件默认定义了该宏),则采用C语言方式进行编译
#endif
int testFun(int, int);
#ifdef __cplusplus
}
#endif

static void testA11() {
//    printf("%d",11);
}
//void testA11(){
////    printf("%d",11);
//}

#endif //TESTC___TESTMODULEA_H
