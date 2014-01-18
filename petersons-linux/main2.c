// This example based off of samples by Jerry Breecher - http://web.cs.wpi.edu/~jb/CS502/Class_Example_Code.html
#include <stdio.h>

#define LOOP 999999

#if !defined(true) && !defined(false)
	#define true 1
	#define false 0
#endif

volatile long gvar = 0;

volatile int turn;
volatile int flag[2];

void * produce(void* data) {
	int i = 0;
	flag[0] = true;
	turn = 1;
	while (flag[1] && turn == 1);
	
	for (i = 0; i < LOOP; i++)
		gvar++;

	flag[0] = false;

}

void * consume(void* data) {
	int i = 0;
	flag[1] = true;
	turn = 0;
	while (flag[0] && turn == 0);
	for (i = 0; i < LOOP; i++)
		gvar--;
	flag[1] = false;
}

int main() {
	int i;
	pthread_t thread1, thread2;
	int  iret1, iret2;
	flag[0] = true;
	flag[1] = true;
	
	iret1 = pthread_create( &thread1, NULL, produce, NULL);
	iret2 = pthread_create( &thread2, NULL, consume, NULL);
	
	pthread_join( thread1, NULL);
    pthread_join( thread2, NULL);
	printf("gvar = %i\n", gvar);
}