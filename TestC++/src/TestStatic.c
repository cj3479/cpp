/*
 * TestStatic.c
 *
 *  Created on: 2018年3月6日
 *      Author: chengjian
 */
void testA(int a){
	static int i=4;
	printf("before %d\n",i);
	i=i+2;
	printf("after %d\n",i);
}
//int main(int argc, char **argv) {
//	testA(5);
//	testA(8);
//	static int i;
//}

