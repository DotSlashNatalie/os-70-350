#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>

int main()
{
        pid_t pid;

        printf("begin\n");
        /* fork a child process */
        pid = fork();
        printf("pid = %i\n", pid);
        if (pid < 0) { /* error occurred */
                fprintf(stderr, "Fork Failed");
                return 1;
        }
        else if (pid == 0) { /* child process */
                execlp("/bin/ls", "ls", NULL);
        }
        else { /* parent process */
                /* parent will wait for the child to complete */
                wait(NULL);
                printf("Child Complete");
        }
        return 0;
	/* output:
	
begin
pid = 15905
pid = 0
[ list of files ]

*/
}
