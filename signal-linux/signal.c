#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <ctype.h>

void sig_handler(int);

int main() {
        int sig = 0;
        for (sig = 1; sig < 255; sig++)
        {
                signal(sig, sig_handler);
        }
        while(1)
                sleep(1);
        return 0;
}

void sig_handler(int sig) {
        char *str = strsignal(sig);
        printf("x.o you hit me with the signal %d -> %s\n", sig, str);
}
