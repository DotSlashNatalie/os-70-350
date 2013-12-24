// This example based off of samples by Jerry Breecher - http://web.cs.wpi.edu/~jb/CS502/Class_Example_Code.html
#include <stdio.h>
#include <windows.h>

#define LOOP 20000

volatile int counter = -1;
volatile long gvar = 0;

DWORD WINAPI produce(void* data) {
	int i = 0;
	for (i = 0; i < LOOP; i++)
		gvar++;
}

DWORD WINAPI consume(void* data) {
	int i = 0;
	for (i = 0; i < LOOP; i++)
		gvar--;
}

int main() {
  int i;
  HANDLE thread1, thread2;
  thread1 = CreateThread(NULL, 0, produce, NULL, 0, NULL);
  thread2 = CreateThread(NULL, 0, consume, NULL, 0, NULL);
  WaitForSingleObject(thread1, INFINITE);
  WaitForSingleObject(thread2, INFINITE);
  printf("gvar = %i\n", gvar);
}