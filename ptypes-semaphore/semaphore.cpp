#include <ptypes/ptypes.h>
#include <ptypes/pasync.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

USING_PTYPES

#define BUFFER_SIZE 10

volatile int buffer[BUFFER_SIZE];
semaphore s(0);

DWORD WINAPI produce(void * data)
{
		int i;
	srand ((unsigned int)time(NULL));
		//while (counter == BUFFER_SIZE - 1);
		
		for (i = 0; i < BUFFER_SIZE; i++)
			buffer[i] = rand() % 20 + 1; // yes I know rand is not thread safe - I just need a way to demonstrate a producing/consuming problem - using the same number doesn't help.
		s.post();
	return 0;

}

DWORD WINAPI consume(void * data)
{
	s.wait();
	int i = 0;
	for(i = 0; i < BUFFER_SIZE; i++)
	{
		printf("CONSUMER value = %i\n", buffer[i]);
		buffer[i] = 0;
	}
	return 0;
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