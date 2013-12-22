#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <windows.h>

#define BUFFER_SIZE 10

volatile int counter = -1;
volatile int buffer[BUFFER_SIZE];

DWORD WINAPI produce(void* data) {
	srand (time(NULL));
	while (1)
	{
		while (counter == BUFFER_SIZE - 1);
		
		buffer[counter + 1] = rand() % 20 + 1; // yes I know rand is not thread safe - I just need a way to demonstrate a producing/consuming problem - using the same number doesn't help.
		printf("PRODUCER value = %i counter = %i\n", buffer[counter + 1], counter + 1);
		counter++;
	}
}

DWORD WINAPI consume(void* data) {
	while(1)
	{
		while (counter == -1);
		if (buffer[counter] == 0)
		{
			printf("%i\n", buffer[counter]);
			printf("Attempting to consume an element that was already consumed counter = %i\n", counter);
			exit(1);
		}
		printf("CONSUMER value = %i counter = %i\n", buffer[counter], counter);
		buffer[counter] = 0;
		counter--;
	}
}

int main() {
  int i;
  HANDLE thread1, thread2;
  for(i = 0; i < BUFFER_SIZE; i++)
	buffer[i] = -1;
  thread1 = CreateThread(NULL, 0, produce, NULL, 0, NULL);
  thread2 = CreateThread(NULL, 0, consume, NULL, 0, NULL);
  WaitForSingleObject(thread1, INFINITE);
  WaitForSingleObject(thread2, INFINITE);
}