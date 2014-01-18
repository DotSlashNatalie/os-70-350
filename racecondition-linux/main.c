#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define BUFFER_SIZE 10

volatile int counter = -1;
volatile int buffer[BUFFER_SIZE];

void * produce(void* data) {
	srand (time(NULL));
	while (1)
	{
		while (counter == BUFFER_SIZE - 1);
		buffer[counter + 1] = rand() % 20 + 1;
		printf("PRODUCER value = %i counter = %i\n", buffer[counter + 1], counter + 1);
		counter++;
	}
}

void * consume(void* data) {
	while(1)
	{
		while (counter == -1);
		printf("CONSUMER value = %i counter = %i\n", buffer[counter], counter);
		buffer[counter] = 0;
		counter--;
	}
}

int main() {
	int i;
	pthread_t thread1, thread2;
	int  iret1, iret2;
	for(i = 0; i < BUFFER_SIZE; i++)
		buffer[i] = -1;
	iret1 = pthread_create( &thread1, NULL, produce, NULL);
	iret2 = pthread_create( &thread2, NULL, consume, NULL);
	
	pthread_join( thread1, NULL);
    pthread_join( thread2, NULL);
	
	return 0;
 
}