#include <iostream>
#include "TestModuleA.h"
#include "TestThread.h"
#include "TestMmapWrite.h"
#include <pthread.h>
#include <unistd.h>
#include <thread>         // std::threa

using namespace std;
#ifdef NM
#pragma message("sadasdd...")
#else
#pragma message("1111...")
#endif
#define NUM 5
#define NUM 8
#include <stdlib.h>
#include <unistd.h>
#define MAXLINE 80
int ffff;
struct epoll_event {
    int a;
};
//extern int ffff;
extern int cc;
extern "C" {
char *testA22();
}

void testA() {
    printf("%d", 11);
}

void testA(int a) {
    printf("%d", a);
}

//int testA(int a){
//    printf("%d",a);
//    return  a;
//}
//int testabc(){
//
//}
//#pragma message("正在编译main函数...")

class Line
{
public:
    void setLength( double len );
    double getLength( void );
    Line();   // 这是构造函数声明
    ~Line();  // 这是析构函数声明

private:
    double length;
};

// 成员函数定义，包括构造函数
Line::Line(void)
{
    cout << "Object is being created="<<this << endl;
}
Line::~Line(void)
{
    cout << "Object is being deleted="<<this << endl;
}

void Line::setLength( double len )
{
    length = len;
}

double Line::getLength( void )
{
    cout <<this<< "  getLength="<< length<< endl;
    return length;
}
void testObejct(Line *line){
    line->setLength(5);

}

//Line lineA;
void testAA(Line lineB){
    printf("testAA 1 lineB=%p\n",&lineB);
    lineB.setLength(20);
    lineB.getLength();
    Line line;
    line.getLength();
}
void *start11(void *data) {
    sleep(2);
    printf("thread start11\n");
//    Line *line = (Line *)data;
//    printf("thread start line.getLength()=%f\n",line->getLength());
//    lineA.getLength();
}
int main() {
    int a1=11;
    int& a2=a1;
    printf("main 1 a1=%d,a2=%d\n",a1,a2);
    int a3 = a2;
    a3=22;
    a1=33;
    a2 =44;
    printf("main 1 a1=%d,a2=%d,a3=%d\n",a1,a2,a3);
    Line lineA;
    lineA.setLength(10);
    lineA.getLength();
    printf("main 1 lineA=%p\n",&lineA);
    testAA(lineA);
    lineA.getLength();
    int n;
    int fd[2];
    pid_t pid;
    char line[MAXLINE];
    printf("main 1 pid=%d\n",getpid());
    if (pipe(fd) < 0) {
        perror("pipe");
        exit(1);
    }
    if ((pid = fork()) < 0) {
        perror("fork");
        exit(1);
    }
    printf("main 2 pid=%d,ppid=%d\n",getpid(),getppid());
    if (pid > 0) { /* parent */
        close(fd[0]);
        write(fd[1], "hello world\n", 12);
        wait(NULL);
    } else {       /* child */
        close(fd[1]);
        n = read(fd[0], line, MAXLINE);
        printf("main 2 line=%s\n",line);
        write(STDOUT_FILENO, line, n);
    }

    char *p = "sfdfdf";
    printf("thread p=%s\n",p);
//    int mWakeEventFd = eventfd(0, EFD_NONBLOCK | EFD_CLOEXEC);
//    Line line1;
//    line.setLength(1);
//    printf("main before line.getLength()=%f\n",line.getLength());
//    Line *line1 = new Line();
//    line1->setLength(100);
    pthread_t thread;
//    //创建一个线程并自动执行
//    int id = pthread_create(&thread, NULL, start11, (void *) lineA);
    int id = pthread_create(&thread, NULL, start11, NULL);
//    testObejct(&line);
//    printf("main after line.getLength()=%f\n",line.getLength());
////    testCreateThread();
//    printf("main pid=%d,ppid=%d,tid=%d\n",getpid(), getppid(),this_thread::get_id());
////    pthread_t thread;
////    //创建一个线程并自动执行
////    int id = pthread_create(&thread, NULL, start, (void *) "this is thread");
////    cout << id << endl;
//    int a = 10;
//    int *p1 = &a;
//    int b = *p1;
//    int c = 2;
//    *p1 = 3;
//    printf("%p,%p,%d\n", p1, &a, a);
////    struct epoll_event epoll;
////    printf("%p\n", epoll);
////    cout << epoll.a<< endl;
//    std::cout << "Hello, World!" << std::endl;
//    testA();
//    testA(22);
//    char *aa = testA22();
//    cout << testFun(2, 3) << endl;
//    cout << "11" << endl;
//    cout << ffff << endl;
//    printf("%p", aa);
    testMMapWrtire();
    return 0;

}
//#pragma message("正在编译main函数...")