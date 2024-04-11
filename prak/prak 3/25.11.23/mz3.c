#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>

void ok(int s){}

void end(int s){exit(0);}

void main_bit(int s)
{
    static int bits = 0;
    static char res = 0;
    if (s == SIGUSR1)
    {
        bits++;
        if (bits != 8) res <<= 1;
    }
    else if (s == SIGUSR2)
    {
        bits++;
        res |= 1;
        if(bits != 8) res <<= 1;
    }

    if (bits == 8)
    {
        printf("%c", res);
        bits = 0;
        res = 0;
    }
}

int main(int argc, char **argv)
{
    pid_t pid1, pid2;
    if (argc != 2){printf("ARGC"); return 0;}

    if ((pid1 = fork()) < 0) {perror("PID1\n"); exit(1);} 

    else if(pid1 == 0) //1-ый сын
    {
        signal(SIGUSR1, main_bit);
        signal(SIGUSR2, main_bit);
        signal(SIGIO, end);
        signal(SIGALRM, SIG_IGN);
        while(1)
        {
            pause();
            kill(0, SIGALRM);
        }
    }

    else if (pid1 > 0)
    {
        signal(SIGUSR1, SIG_IGN);
        signal(SIGUSR2, SIG_IGN);
        signal(SIGIO, SIG_IGN);
        
        if ((pid2 = fork()) < 0) {perror("PID2\n"); exit(1);} 

        else if (pid2 == 0) //2-ой сын
        {
            signal(SIGALRM, ok);
            int f;
            f = open(argv[1], O_RDONLY);
            if (f == -1) {printf("F");return 0;}
            char c; 
            int tmp;
            //printf("FILE OPENED\n");
            while((read(f, &c, sizeof(char))))
            {
                for (int i = 7; i >= 0; i--)
                {
                    tmp = (c >> i) & 1;
                    if (tmp == 0) {kill(0, SIGUSR1);}
                    else {kill(0, SIGUSR2);}
                    pause();
                }
            }
            kill(0, SIGIO); close(f); exit(0);
        }
        else if (pid2 > 0)//отец
        {
            signal(SIGALRM, SIG_IGN);
            wait(0); wait(0);
            return 0;
        }
    }
}