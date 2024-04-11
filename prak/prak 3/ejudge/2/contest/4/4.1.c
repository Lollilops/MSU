#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdio.h>

int
main(int argc, char *argv[])
{
    int status;
    if (argc < 6)
        return 0;
    pid_t pid;
    int fd_f;

    int fd[2];
    pipe(fd);
    
    if(!(pid = fork()))
    {
        close(fd[0]);
        dup2(fd[1], 1);
        close(fd[1]);

        if(!(pid = fork()))
        {
            fd_f = open(argv[4], O_RDONLY, 0666);
            dup2(fd_f, 0);
            close(fd_f);

            execlp(argv[1], argv[1], NULL);
            _exit(1);
        }

        waitpid(pid, &status, 0);

        if(WIFEXITED(status) && (!WEXITSTATUS(status)))
        {
            if(!(pid = fork()))
            {
                execlp(argv[2], argv[2], NULL);
                _exit(1);
            }
            waitpid(pid, NULL, 0);
            _exit(0);
        }
        else
        {
            _exit(0);
        }
    }

    
    close(fd[1]);

    if(!(pid = fork()))    
    {
        dup2(fd[0], 0);
        close(fd[0]);

        fd_f = open(argv[5], O_CREAT | O_WRONLY | O_APPEND, 0666);
        dup2(fd_f, 1);
        close(fd_f);

        execlp(argv[3], argv[3], NULL);
        _exit(1);
    }
    close(fd[0]);

    while (wait(NULL) > 0);

    return 0;
}