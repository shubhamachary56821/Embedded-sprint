#include <stdio.h>
#include <signal.h>
#include <unistd.h>

int flag = 0;

void handler(int s){
    (void)s;
    flag = 1;
}

int main(void) {
    signal(SIGALRM, handler);   // 1. install handler first
    alarm(1);                   // 2. then start the timer
    while (!flag) { }
    printf("flag seen, exiting\n");
    return 0;
}