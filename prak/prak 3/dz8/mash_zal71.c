#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <string.h>

int main(int argc, char **argv)
{
    if (argc != 6) {fprintf(stderr, "wrong0");}
    int st;
    int n;
    pid_t pid; 
    pid_t pid1;
    if (strcmp(argv[5], "p") == 0)
    {
        if ((pid = fork()) < 0) {fprintf(stderr, "WRONG1");}

        else if (pid == 0)
        {
            execl(argv[1], argv[1], argv[2], NULL);
            fprintf(stderr, "WRONG2");
            exit(1);
        }
        else 
        {
            if ((pid1 = fork()) < 0) {fprintf(stderr, "WRONG1");}

            else if (pid1 == 0)
            {
                execl(argv[3], argv[3], argv[4], NULL);
                fprintf(stderr, "WRONG3");
                exit(1);
            }
            waitpid(pid,&st,0);
            if (WIFEXITED(st)) printf("%d\n", WEXITSTATUS(st));
            else if (WIFSIGNALED(st))  printf("%d\n", WTERMSIG(st));
            waitpid(pid1,&st,0);
            if (WIFEXITED(st)) printf("%d\n", WEXITSTATUS(st));
            else if (WIFSIGNALED(st)) printf("%d\n", WTERMSIG(st));
        }
    }
    else if (strcmp(argv[5], "s") == 0)
    {
        if ((pid = fork()) < 0) {fprintf(stderr, "WRONG11");}

        else if (pid == 0)
        {
            execl(argv[1], argv[1], argv[2], NULL);
            fprintf(stderr, "WRONG22"); exit(1);
        }
        else 
        {
            waitpid(pid,&st,0);
            if (WIFEXITED(st)) printf("%d\n", WEXITSTATUS(st));
            else if (WIFSIGNALED(st)) printf("%d\n", WTERMSIG(st));

            if ((pid1 = fork()) < 0) {fprintf(stderr, "WRONG1");}

            else if (pid1 == 0)
            {
                execl(argv[3], argv[3], argv[4], NULL);
                fprintf(stderr, "WRONG3");
                exit(1);
            }
            waitpid(pid1,&st,0);
            if (WIFEXITED(st)) printf("%d\n", WEXITSTATUS(st)); //если exit
            else if (WIFSIGNALED(st)) printf("%d\n", WTERMSIG(st)); // если abort
        }
    }
}