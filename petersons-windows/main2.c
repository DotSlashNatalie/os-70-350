// This example based off of samples by Jerry Breecher - http://web.cs.wpi.edu/~jb/CS502/Class_Example_Code.html
#include <stdio.h>
#include <windows.h>

#define LOOP 999999

#if !defined(true) && !defined(false)
	#define true 1
	#define false 0
#endif

volatile long gvar = 0;

volatile int turn;
volatile int flag[2];

DWORD WINAPI produce(void* data) {
	int i = 0;
	flag[0] = true;
	turn = 1;
	while (flag[1] && turn == 1);
	
	for (i = 0; i < LOOP; i++)
		gvar++;

	flag[0] = false;

}

DWORD WINAPI consume(void* data) {
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
	HANDLE thread1, thread2;
	flag[0] = true;
	flag[1] = true;
	
	thread1 = CreateThread(NULL, 0, produce, NULL, 0, NULL);
	thread2 = CreateThread(NULL, 0, consume, NULL, 0, NULL);
	WaitForSingleObject(thread1, INFINITE );
	WaitForSingleObject(thread2, INFINITE );
	printf("gvar = %i\n", gvar);
}