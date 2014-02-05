#include <ptypes/ptypes.h>
#include <ptypes/pasync.h>
#include <stdio.h>
#include <windows.h>

USING_PTYPES


#define LOOP 20000

volatile int counter = -1;
volatile unsigned long gvar = 0;
mutex m_lock;

DWORD WINAPI produce(void* data) {
	scopelock l(m_lock);
	int i = 0;
	for (i = 0; i < LOOP; i++)
		gvar++;
	return 0;
}

DWORD WINAPI consume(void* data) {
	scopelock l(m_lock);
	int i = 0;
	for (i = 0; i < LOOP; i++)
		gvar--;
	return 0;
}

int main() {
  HANDLE thread1, thread2;
  thread1 = CreateThread(NULL, 0, produce, NULL, 0, NULL);
  thread2 = CreateThread(NULL, 0, consume, NULL, 0, NULL);
  WaitForSingleObject(thread1, INFINITE);
  WaitForSingleObject(thread2, INFINITE);
  printf("gvar = %lu\n", gvar);
}