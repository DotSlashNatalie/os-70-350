#include <stdio.h>
#include <pthread.h>

#define LOOP 20000

volatile long gvar = 0;

void * produce(void* data) {
	int i = 0;
	for (i = 0; i < LOOP; i++)
		gvar++;
}

void * consume(void* data) {
	int i = 0;
	for (i = 0; i < LOOP; i++)
		gvar--;
}

int main() {
	int i;
	pthread_t thread1, thread2;
	int  iret1, iret2;
	iret1 = pthread_create( &thread1, NULL, produce, NULL);
	iret2 = pthread_create( &thread2, NULL, consume, NULL);
	
	pthread_join( thread1, NULL);
    pthread_join( thread2, NULL);
	printf("gvar = %lu\n", gvar);
}