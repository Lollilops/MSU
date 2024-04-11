#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
 
pid_t pid1, pid2;
//volatile int flag = 0;

void ok(int s){} //flag = 1;

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
    kill(0, SIGALRM);

}

int main(int argc, char **argv)
{
    if (argc != 2){printf("ARGC"); return 0;}

    signal(SIGALRM, ok);

    if ((pid1 = fork()) < 0) {perror("PID1\n"); exit(1);} 

    else if(pid1 == 0) //1-ый сын
    {
        signal(SIGUSR1, main_bit);
        signal(SIGUSR2, main_bit);
        signal(SIGIO, end);
        while(1)
        {
            pause();
            //printf("SIG CAAME\n");
        }
    }

    else 
    {
        if ((pid2 = fork()) < 0) {perror("PID2\n"); exit(1);} 

        else if(pid2 == 0) //2-ой сын
        {
            sleep(1); //Чтобы в первойм процессе успели установиться фу-ии обработчики
            //printf("PID2 %d : %d", pid2, getpid());
            int len = 1;
            char c; 
            int f;
            f = open(argv[1], O_RDONLY);
            if (f == -1) {printf("F");return 0;}
            int tmp;
            //printf("FILE OPENED\n");
            while((len = read(f, &c, sizeof(char))))
            {
                for (int i = 7; i >= 0; i--)
                {
                    tmp = (c >> i) & 1;
                    if (tmp == 0){kill(pid1, SIGUSR1);}
                    else{kill(pid1, SIGUSR2);}
                    pause();
                    // if(flag == 0) {kill(pid1, SIGIO); close(f); exit(0);}
                    // flag = 0;
                }
            }
            if (len == 0) {kill(pid1, SIGIO); close(f); exit(0);}
        }
        else //отец
        {
            // signal(SIGALRM, SIG_IGN);
            wait(0); wait(0);
            return 0;
        }
    }
}