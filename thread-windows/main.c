#include <stdio.h>
#include <windows.h>

DWORD WINAPI ThreadFunc(void* data) {
	int i;
	for(i = 0; i < 10; i++)
		printf("%i\n", i);
	return 0;
}

int main() {
  HANDLE thread1, thread2;
  thread1 = CreateThread(NULL, 0, ThreadFunc, NULL, 0, NULL);
  thread2 = CreateThread(NULL, 0, ThreadFunc, NULL, 0, NULL);
  WaitForSingleObject(thread1, INFINITE);
  WaitForSingleObject(thread2, INFINITE);
}