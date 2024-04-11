#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/signal.h>
#include <unistd.h>
pid_t pid;

void father(int s){
    printf("Father\n");
    kill(pid, SIGUSR1);
}

void son(int s){
    printf("Son\n");
    kill(pid, SIGUSR1);
}

void salarm(int s){
    exit(0);
}

int main(){
    signal(SIGUSR1, father);
    pid = fork();
    if (pid == 0) {
        signal(SIGUSR1, son);
        signal(SIGALRM, salarm);
        alarm(2);
        pid = getppid();
        kill(pid, SIGUSR1);
        while (1)
            pause();
    } else {
        wait(0);
        while (1) {
            sleep(1);
            printf("Father\n");
        }
    }
    return 0;
}
