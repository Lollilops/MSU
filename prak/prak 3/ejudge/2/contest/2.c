#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
//#include <fcntl.h>
//#include <sys/types.h>


int main()
{
    pid_t pid;
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        if (i == n){printf("%d\n", i); exit(0);}
        printf("%d ", i);
        fflush(stdout);
        if((pid = fork()))
        {
            wait(0);
            break;
        }
    }
    return 0;
}