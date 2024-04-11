#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
//./a.out cmd1 cmd2 cmd3 file1 file2
int main(int argc, char **argv)
{
    int fd[2];
    pipe(fd);
    pid_t pid1, pid2, pid3, pid_main;
    int status1, status2;
    if ((pid_main = fork()) == 0)
    {
        dup2(fd[1], 1);
        close(fd[0]);
        close(fd[1]);
        if ((pid1 = fork()) == 0)
        {
            int f1 = open(argv[4], O_RDONLY);
            dup2(f1, 0);
            execlp(argv[1], argv[1], NULL);
            exit(1);
        }
        waitpid(pid1, &status1, 0);

        if (!status1) //если первая норм отработала
        {
            if((pid2 = fork()) == 0)
            {
                execlp(argv[2], argv[2], NULL);
                exit(1);
            }
            wait(0);
        }
        exit(0);
    }
    
    close(fd[1]);
    if((pid3 = fork()) == 0)
    {
        int f2 = open(argv[5], O_RDWR | O_APPEND | O_CREAT, 0666);
        dup2(f2, 1);
        dup2(fd[0], 0);
        execlp(argv[3], argv[3], NULL);
        exit(1);
    }
    close(fd[0]);
    wait(0);
    wait(0);
    return 0;
}
