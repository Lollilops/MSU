#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <string.h>
#include <fcntl.h>


int main(int argc, char **argv)
{
    if (argc != 6) {perror("argc");}

    int fd[2];
    pipe(fd); //открывается канал 

    int fd1; 
    int pid, pid1; 
    if ((pid = fork()) < 0) {perror("WRONG"); exit(1);}
    
    else if (pid == 0)
    {
        dup2(fd[1], 1); //канал на запись
        close(fd[1]);
        close(fd[0]); // закрываем канал на чтение, чтоб он ничего не ждал и завершился 

        execlp(argv[1], argv[1], argv[2], NULL); //результат первого процесса будет в канале 
        perror("wrong"); exit(1);
    }

    if ((pid1 = fork()) < 0) {perror("WRONG1"); exit(1);}    
    
    else if (pid1 == 0)
    {
        dup2(fd[0], 0); // заменили stdin на чтение из канала 
        close(fd[1]);
        close(fd[0]);
        fd1 = open(argv[5], O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (fd1 == -1) {printf("WRONG"); return -1;}

        dup2(fd1, 1); //будет записывать в файл а не на вывод
        execlp(argv[3], argv[3], argv[4], NULL);
        perror("WRONG2"); exit(1);
    }

    close(fd[1]);
    close(fd[0]);

    wait(0); wait(0);

    return 0;
}