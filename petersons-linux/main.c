#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define BUFFER_SIZE 10

#if !defined(true) && !defined(false)
	#define true 1
	#define false 0
#endif

volatile int counter = -1;
volatile int buffer[BUFFER_SIZE];

volatile int turn;
volatile int flag[2];

void * produce(void* data) {
	srand (time(NULL));
	while (true)
	{
		flag[0] = true;
		turn = 1;
		while (flag[1] && turn == 1);
		if (counter == BUFFER_SIZE - 1) // make sure the buffer doesn't overflow
		{
			flag[0] = false;
			sleep(5);
			continue;
		}
		
		
		buffer[counter + 1] = rand() % 20 + 1; // yes I know rand is not thread safe - I just need a way to demonstrate a producing/consuming problem - using the same number doesn't help.
		printf("PRODUCER value = %i counter = %i\n", buffer[counter + 1], counter + 1);
		counter++;
		flag[0] = false;

	}
}

void * consume(void* data) {
	int i = 0;
	while(true)
	{
		flag[1] = true;
		turn = 0;
		while (flag[0] && turn == 0);
		if (counter == -1) // producer hasn't produced - make sure there is content to consume
		{
			flag[1] = false;
			continue;
		}
		if (buffer[counter] == 0)
		{
			for(i = 0; i < BUFFER_SIZE; i++)
				printf("%i\n", buffer[i]);
			printf("Attempting to consume an element that was already consumed counter = %i\n", counter);
			exit(1);
		}
		printf("CONSUMER value = %i counter = %i\n", buffer[counter], counter);
		buffer[counter] = 0;
		counter--;
		flag[1] = false;
		sleep(1);
	}
}

int main() {
	int i;
	pthread_t thread1, thread2;
	int  iret1, iret2;
	for(i = 0; i < BUFFER_SIZE; i++)
		buffer[i] = -1;
	flag[0] = true;
	flag[1] = true;
	
	iret1 = pthread_create( &thread1, NULL, produce, NULL);
	iret2 = pthread_create( &thread2, NULL, consume, NULL);
	
	pthread_join( thread1, NULL);
    pthread_join( thread2, NULL);
}