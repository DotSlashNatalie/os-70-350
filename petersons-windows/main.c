#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <windows.h>

#define BUFFER_SIZE 10

#if !defined(true) && !defined(false)
	#define true 1
	#define false 0
#endif

volatile int counter = -1;
volatile int buffer[BUFFER_SIZE];

volatile int turn;
volatile int flag[2];

DWORD WINAPI produce(void* data) {
	srand (time(NULL));
	while (true)
	{
		flag[0] = true;
		turn = 1;
		//while (counter == BUFFER_SIZE - 1); // make sure the buffer doesn't overflow
		while (flag[1] && turn == 1);
		if (counter == BUFFER_SIZE - 1)
		{
			continue;
			flag[0] = false;
		}
		
		
		buffer[counter + 1] = rand() % 20 + 1; // yes I know rand is not thread safe - I just need a way to demonstrate a producing/consuming problem - using the same number doesn't help.
		printf("PRODUCER value = %i counter = %i\n", buffer[counter + 1], counter + 1);
		counter++;
		flag[0] = false;

	}
}

DWORD WINAPI consume(void* data) {
	while(true)
	{
		flag[1] = true;
		turn = 0;
		//while (counter == -1); // make sure there is content to consume
		while (flag[0] && turn == 0);
		if (counter == -1) // producer hasn't produced
		{
			flag[1] = false;
			continue;
		}
		if (buffer[counter] == 0)
		{
			printf("%i\n", buffer[counter]);
			printf("Attempting to consume an element that was already consumed counter = %i\n", counter);
			exit(1);
		}
		printf("CONSUMER value = %i counter = %i\n", buffer[counter], counter);
		counter--;
		buffer[counter] = 0;
		flag[1] = false;
	}
}

int main() {
	int i;
	HANDLE thread1, thread2;
	for(i = 0; i < BUFFER_SIZE; i++)
		buffer[i] = -1;
	flag[0] = true;
	flag[1] = true;
	
	thread1 = CreateThread(NULL, 0, produce, NULL, 0, NULL);
	thread2 = CreateThread(NULL, 0, consume, NULL, 0, NULL);
	WaitForSingleObject(thread1, 50);
	WaitForSingleObject(thread2, 50);
}