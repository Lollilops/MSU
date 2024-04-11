#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <errno.h>

int main(int argc, char **argv)
{
    if (argc != 4) {perror("argc");}

    pid_t pid1, pid2, pid3;
    int status1, status2, status3;

    if((pid1 = fork()) == 0)
    {
        execlp(argv[1], argv[1], NULL);
        //perror("execl(argv[1])");
        exit(1);
    }

    waitpid(pid1, &status1, 0); //узнаем как завреш. cmd1

    if(status1) 
    {
        if((pid2 = fork()) == 0)
        {
            execlp(argv[2], argv[2], NULL);
            //perror("execl(argv[2])"); 
            exit(1);
        }
        waitpid(pid2, &status2, 0); //узнаем как завреш. cmd2
    }
    
    if ((!status1) || (!status2))
    {
        if((pid3 = fork()) == 0)
        {
            execlp(argv[3], argv[3], NULL);
            //perror("execl(argv[3])");
            exit(1);
        }
        waitpid(pid3, &status3, 0); //узнаем как завреш. cmd3
        if (status3) {exit(1);}
        else {exit(0);}
    }
    else 
    {
        // printf("1 or 2 BAD\n");
        exit(1);
    }
    
}