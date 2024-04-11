#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <wait.h>

int main(int argc, char **argv)
{
    pid_t pid1;
    int status1;

    if ((pid1 = fork()) == 0)
    {
        int f1 = open(argv[2], O_RDONLY);
        dup2(f1, 0);
        execlp(argv[1], argv[1], NULL);
    }

    waitpid(pid1, &status1, 0);
    return 0;
}
//при запуске ./4_tmp 4_1 t1.txt
//ничего не работает