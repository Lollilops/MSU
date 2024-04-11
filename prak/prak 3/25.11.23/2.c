#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/signal.h>
#include <sys/file.h>
#include <string.h>
#include <unistd.h>
#define MAXLEN 20
pid_t pid;
int f;
char *st, bykva;
int l1=0;

void father(int s){
    st = malloc(MAXLEN+1);
    int x;
    while ((x = read(f, &bykva, 1)) == 1 && bykva != ' ' && bykva != '\n') {
        st[l1] = bykva;
        l1++;
    }
    st[l1] = '\0';
    l1 = 0;
    printf("Father %s\n", st);
    if (x != 0){
        kill(pid, SIGUSR1);
    }
}

void son(int s){
    st = malloc(MAXLEN+1);
    int x;
    while ((x = read(f, &bykva, 1)) == 1 && bykva != ' ' && bykva != '\n') {
        st[l1] = bykva;
        l1++;
    }
    st[l1] = '\0';
    l1 = 0;
    printf("Son %s\n", st);
    if (x != 0){
        kill(pid, SIGUSR1);
    }
}

void salarm(int s){
    exit(0);
}

int main(int argc, char **argv){
    if ((f = open(argv[1], O_RDONLY)) == -1) {
        return 0;
    }

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
    close(f);
    return 0;
}
