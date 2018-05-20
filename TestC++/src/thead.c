/*
 * =====================================================================================
 *       Filename:  thead.c
 *    Description:  getspecific
 *        Created:  05/10/2011 12:09:43 AM
 * =====================================================================================
 */
#include<stdio.h>
#include<pthread.h>
#include<string.h>
pthread_key_t p_key;
pthread_mutex_t gTLSMutex = PTHREAD_MUTEX_INITIALIZER;
void func1() {
	int *tmp = (int*) pthread_getspecific(p_key); //同一线程内的各个函数间共享数据。
	printf("%d,%d isddddd runing in %s\n", *tmp, tmp, __func__);

}
void *thread_func(void *args) {
	pthread_mutex_lock(&gTLSMutex);
	pthread_setspecific(p_key, args);
	int *tmp = (int*) pthread_getspecific(p_key); //获得线程的私有空间
	printf("%d is thread_func runing in %s,%d,%d,%d\n", *tmp, __func__, p_key,
			&p_key, tmp);
//	sleep(2);
	int *aa = args;
	printf("args is %d ,%d \n", args, *aa);

	*tmp = (*tmp) * 100; //修改私有变量的值

	func1();
	pthread_mutex_unlock(&gTLSMutex);
	return (void*) 0;
}
void swap(int a, int b) {
	printf("%p,%p\n", &a, &b);
}
//int main() {
//	for (int i = 0; i < 5; i++) {
//		 int aa = 10;
//		aa++;
//		printf("%d is runing in \n", aa);
//	}
////	pthread_t pa, pb;
////	printf("%d is runing in \n", p_key);
////	int a = 1;
////	int b = 2;
////	swap(a,b);
////	printf("%p,%p\n", &a, &b);
////	int result0 = pthread_key_create(&p_key, NULL);
////	int *aa = &a;
////	printf("%d is runing in %d,%d\n", p_key, aa, *aa);
////	int result1 = pthread_create(&pa, NULL, thread_func, aa);
////	int result2 = pthread_create(&pb, NULL, thread_func, &b);
////	printf("result1  is %d, result2 is %d\n", result0,result1, result2);
////	pthread_join(pa, NULL);
////	pthread_join(pb, NULL);
////	printf("main thread end\n");
////	sleep(2);
//	return 0;
//}
