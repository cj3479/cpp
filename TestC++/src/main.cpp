#include <iostream>
#include <memory>
#include <zconf.h>
#include <sys/syscall.h>
//#include "TestExternal.h"
#define __NR_gettid 186

#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

using namespace std;
#define N 65.0
const int nn = 65;

//extern void testAA();

void *threadwrite(void *data) {
    printf("sub thread start\n");
    pthread_mutex_lock((pthread_mutex_t *) data);
    sleep(4);
    pid_t pid = fork();
    std::cout << "sub thread start pid=" << pid << "  getPid=" << getpid() << " sub thread=" << pthread_self()
              << std::endl;
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
    std::cout << "sub thread end pid=" << pid << "  getPid=" << getpid() << " sub thread=" << pthread_self()
              << std::endl;
    pthread_mutex_unlock((pthread_mutex_t *) data);
}

//void testPointer(int *p) {
//    (*p) = (*p) + 10;
//}

void testReference(int &r) {
    printf("r =%d,%p\n", r, &r);
    r = r + 10;

}
//extern "C"{
// void testPointer(int *p);
//}
//int main() {
//    int i = 5;
//    int j = 6;
//    int &k = i;
//    int a = 11;
//    int *p = &a;
//    p = &j;
//    k= j;
////    *p = 20;
//    k = 10; // k 和 i 的值都变成了 6;
////    testPointer(p);
//    printf("a =%p\n", &a);
//    testReference(a);
//    int *pp = const_cast<int *>(&nn);
//    printf("thread =%d,%d,%d,%d,%c,%d\n", k, i, a, N,nn,&nn);
////    int aa = 10;
////    std::cout << "Hello, World!" << std::endl;
//////    testAA();
////    pthread_t tid = pthread_self();
////    std::cout << "Hello, World pid=" << getpid() <<"  tid="<<tid<< std::endl;
////    pid_t pid = getpid();
////    pthread_t thread;
////    pthread_mutex_t pLock;
////    pthread_mutex_init(&pLock, NULL);
////    //创建一个线程并自动执行
////    int id = pthread_create(&thread, NULL, threadwrite, &pLock);
////    printf("thread =%p\n",thread);
////    sleep(1);
////    pthread_mutex_lock(&pLock);
////    pthread_mutex_unlock(&pLock);
//////    pid_t pid = fork();
//////    std::cout << "Hello, World111 pid=" << pid << "  getPid=" << getpid() << std::endl;
//////    if (pid == 0) {
//////        int j;
//////        for (j = 0; j < 1; j++) {
//////            printf("child: %d pid=%d,ppid=%d,aa=%d\n", j, getpid(), getppid(), aa);
////////            sleep(1);
//////        }
//////    } else if (pid > 0) {
//////        int i;
//////        for (i = 0; i < 1; i++) {
//////            printf("parent: %d pid=%d,ppid=%d\n", i, getpid(), getppid());
////////            sleep(1);
//////        }
//////    } else {
//////        fprintf(stderr, "can't fork ,error %d\n", errno);
//////        exit(1);
//////    }
//////    printf("This is the end !");
////    printf("main thread end\n");
//    return 0;
//}
class TestSuper {
    virtual void f(){};
};
class Test:TestSuper {
public:
    Test() {
        str = "sss";
        cout << "Test creat():"<<str<<"\n";
    }
    Test(string s) {
        str = s;
        cout << "Test creat(str):"<<str<<"\n";
    }
//    void f(){
//        cout << "Test creat:"<<str<<"\n";
//    };
    ~Test() {
        cout << "Test delete:" << str << "  this=" << this << endl;
    }

    string &getStr() {
        return str;
    }

    void setStr(string s) {
        str = s;
    }

    void print() {
        cout << str << endl;
    }

public:
    string str;
//    char value;
//    double value1;
};

class Test1 {
public:
    Test1(string s):test11("sdsdsd") {
        str11 = s;
        cout << "Test1 creat\n";
//        test11().setStr("fdfdfdf")
    }



public:
    char a1;
    int a;
    string str11;
    Test test11;
};

int max(int x, int y) {
    return x > y ? x : y;
}


int *getMax(int a, int b) {
    return a > b ? &a : &b;
}

void testFork() {
    printf("before 百度百科：pid=%d,ppid=%d\n", getpid(), getppid());
    int p1[2];
    int a = 10;
    int result = pipe(p1);
    pid_t pid = fork();/*传递参数*/
    printf("fdsfdsfd %d=\n", getpid());
//    sleep(5);
    if (pid < 0)/*如果(进程标记<0)*/
    {
//		fprintf(stderr, "错误！");
        printf("error");
    } else if (pid == 0)/*否则如果(进程标记==0)*/
    {
        sleep(15);
        printf("百度百科：这是子进程pid=%d,ppid=%d,p[0]=%d,p[1]=%d,a=%d\n", getpid(), getppid(), p1[0], p1[1], a);
//		exit(0);
    } else/*否则*/{
        printf("百度百科：这是父进程！子进程的进程标记为=%d,p[0]=%d,p[1]=%d,a=%d\n", pid, p1[0], p1[1], a);
    }
    printf("after 百度百科：pid=%d,ppid=%d\n", getpid(), getppid());
}
//Test *test1;
void *threadRun(void *data) {
    sleep(1);
//    Test *test4 = new Test("test4");
    printf("threadRun11：%p\n", data);
//    test1->print();
//    delete test1;
    cout <<"threadRun:"<<((Test *) data)<<endl;
//    Test *test = (Test *)(* data);
//    printf("threadRun：%p\n", data);
//    cout <<"threadRun test1.str:"<<test1->str<<endl;
    cout << "threadRun：" << (unique_ptr<Test> *) data << endl;
    cout << "threadRun：" << *((unique_ptr<Test> *) data) << endl;
    cout <<"threadRun data.str:"<<((Test *) data)->str<<endl;
    cout <<"threadRun data.str:"<<(*(unique_ptr<Test> *) data)->str<<endl;
//    cout <<"threadRun11 data.str:"<<(*(unique_ptr<Test> *) data)->str<<endl;
    printf("threadRun22：%p\n", data);
//    ((Test *) data)->print();
//    cout << "threadRun：" << ((Test *) data)->print() << endl;
//    TestSuper *test4 = new TestSuper();
//    cout <<"threadRun11 data.str:"<<(*(unique_ptr<Test> *) data)->str<<endl;
//    Test *dd = dynamic_cast<Test*>(*(unique_ptr<Test> *) data);
    cout << "threadRun：get=" << (*(unique_ptr<Test> *) data) << endl;
}

void testAutoPtr();

int main(int argc1, char* const argv1[]) {

//    sleep(10);
    printf("main getpid=%d\n", getpid());
//    char * argv[] = {"TestMainExc"};
//    char * envp[] = {"PATH=.", 0};
    char * argv[] = {"ls", (char *)0};
//    char * argv[] = {"ls", "-al", "/etc/passwd", (char *)0};
    char * envp[] = {"PATH=/bin", 0};
    int result=-10;
//    result = execve("/bin/ls", argv, NULL);
    char * argv2[] = {"TestMainExc", (char *)0};
//    int result1 = execve("TestMainExc", argv2, NULL);
//    printf("result=%d,result1=%d\n", result,result1);
    printf("argv1=%s\n", argv1[0]);
//    sleep(20);
    testFork();
    int *p1 = getMax(10, 20);
    sleep(20);
//    printf("p1=%p\n", p1);
//    printf("较大的数值是：%d\n", *p1);
    int (*p)(int, int);
    p = max;
    int a = p(10, 10);
    printf("aaaaa=%d\n", a);
//    int (* p)(int, int) = & max;
//    unique_ptr<Test> ptest1;
    testAutoPtr();
//    int aa =10;
//    int bb =10;
//    int *p2=&aa;
//    int *p3=&bb;
//    printf("p2=%p,p3=%p,p3.size=%d\n", &p2,&p3, sizeof(p2));
//    printf("p2=%p,p3=%p,p3.size=%d\n", p2,p3, sizeof(p2));
    sleep(6);
    return 0;
}
//Test *test1;
void testAutoPtr() {
    Test *test0 = new Test("test0");
//    Test *test1 = new Test("test1");
//    test1 = new Test("test1");
//    Test *test2 = test1;
//    printf("test0=%p\n", test0);
//    printf("test0.add=%p\n", &test0);
//    printf("test1=%p\n", test1);
//    printf("test1.ddd=%p\n", &test1);
//    printf("test2=%p\n", test2);
//    printf("test2.ddd=%p\n", &test2);
//    test1->print();
//    test2->print();
//    unique_ptr<Test> ptest(test1);
    unique_ptr<Test> ptest(test0);
////    delete test1;
    printf("ptest.get=%p\n",ptest.get());
    printf("ptest=%p\n",&ptest);
//    ptest->setStr("hello ");
    ptest->print();
//    ptest.get()->print();
//    ptest->getStr() += "world !";
//    (*ptest).print();
//    if(ptest.get() == NULL)cout<<"ptest = NULL\n";
//    printf("较大的数值是：%p\n",ptest.get());
//    ptest = std::make_unique<Test>("123");
//    ptest->print();
//    Test *test = new Test("sadsdsf");
////    cout<<"*test="<<(*test);
//    cout<<"test="<<test<<endl;
//    printf("test=%p\n",test);
//    cout<<"ptest.get="<<(*(&ptest))<<endl;
////    printf("ptest.get=%p\n",(*(&ptest)));
//    printf("ptest=%p\n",&ptest);
//    printf("test=%p\n",*test);
//    test->print();
    pthread_t thread;
//    pthread_mutex_t pLock;
//    pthread_mutex_init(&pLock, NULL);
    //创建一个线程并自动执行
//    test1 = NULL;
//    delete (test0);

//    delete (test2);
    sleep(2);
//    int *array=new int[32];
//    int *array1=new int[32];
//    Test1 *test3 = new Test1("cccc");
//    Test *test4 = new Test("aaaa");
//    Test *test5 = new Test("bbbbb");
//    test1->print();
//    test2->print();
//    (*test1).print();
//    (*&test1)->print();
//    int id = pthread_create(&thread, NULL, threadRun, test1);
    cout<<"before ptest.get="<<(*(&ptest))<<endl;
    int id = pthread_create(&thread, NULL, threadRun, &ptest);
//    sleep(2);
//    delete (test0);
    cout<<"after ptest.get="<<(*(&ptest))<<endl;
    printf("after ptest.get=%p\n",ptest.get());
    printf("test0=%p\n",test0);
//    delete (test0);
//    printf("test1=%p\n",test1);
//    printf("test2=%p\n",test2);
//    printf("array=%p\n",array);
//    printf("test3=%p\n",test3);
////    printf("test4=%p\n",test4);
////    printf("test5=%p\n",test5);
////    printf("test0.add=%p\n",&test0);
//    printf("test1.add=%p\n",&test1);
//    printf("test2.add=%p\n",&test2);
//    printf("test3.add=%p\n",&test3);
//    printf("size(test)=%d,size(int)=%d\n", sizeof(Test),sizeof(int));
//    Test *test3 = test1;
//    test2->print();
}