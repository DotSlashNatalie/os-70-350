#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *print_message_function( void *ptr )
{
	int i;
	for(i = 0; i < 10; i++)
		printf("%i", i);
}

int main()
{
	pthread_t thread1, thread2;
	int  iret1, iret2;
	iret1 = pthread_create( &thread1, NULL, print_message_function, NULL);
	iret2 = pthread_create( &thread2, NULL, print_message_function, NULL);
	
	pthread_join( thread1, NULL);
    pthread_join( thread2, NULL);
	
	return 0;
}