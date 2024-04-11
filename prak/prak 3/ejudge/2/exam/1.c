// #include <stdio.h>
// #include <stdlib.h>
// #include <sys/pipe.h>
// #include <sys/file.h>
// #include <unistd.h>
// #include <fcntl.h>

// int main(int argc, char **argv){

//     int fd[2];
//     pipe(fd);
//     pid_t pid1, pid2, pid3, pid4, pid_main;

//     if((pid1 = fork()) == 0){
//         dup2(fd[1], 1);
//         dup2(fd[0], 0);
//         close(fd[1]);
//         close(fd[0]);
//         execlp(argv[1], argv[1], NULL);
//         exit(1);
//     }
//     wait(0);
//     if((pid_main = fork()) == 0){
//         int f1 = open(argv[3], O_WRONLY | O_CREAT, 0666);
//         dup2(fd[0], 0);
//         close(fd[0]);
//         close(fd[1]);
//         if((pid2 = fork()) == 0){
//             dup2(f1, 1);
//             close(f1);
//             execlp(argv[2], argv[2], NULL);
//             exit(1);
//         }

//         int status;
//         waitpid(pid2, &status, 0);

//         if (!WIFEXITED(status) && (WEXITSTATUS(status))) //если первая не норм отработала
//         {
//             if((pid3 = fork()) == 0)
//             {
//                 execlp(argv[4], argv[4], NULL);
//                 exit(1);
//             }
//             wait(0);
//         }
//         exit(0);
//     }
//     // close(fd[1]);
//     if((pid4 = fork()) == 0){
//         dup2(fd[0], 0);
//         dup2(1, 1);
//         execlp(argv[5], argv[5], NULL);
//         exit(1);
//     }
//     close(fd[0]);
//     close(fd[1]);
//     return 0;
// }

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>
#include <limits.h>
#include <errno.h>

int main(int argc, char** argv) {
    int fd1[2];
    int fd2[2];
    pipe(fd1);
    if (fork() == 0) {
        close(fd1[0]);
        dup2(fd1[1], 1);
        close(fd1[1]);
        execlp(argv[1], argv[1], NULL);
        _exit(1);
    }
    pipe(fd2);
    if (fork() == 0) {
        close(fd1[1]);
        dup2(fd1[0], 0);
        close(fd1[0]);
        pid_t pid;
        int status;
        close(fd2[0]);
        dup2(fd2[1], 1);
        close(fd2[1]);
        if ((pid = fork()) == 0) {
            int fd = open(argv[3], O_WRONLY | O_CREAT | O_TRUNC, 0666);
            dup2(fd, 1);
            close(fd);
            execlp(argv[2], argv[2], NULL);
            _exit(1);
        }
        waitpid(pid, &status, 0);
        if (!WIFEXITED(status)) {
            execlp(argv[4], argv[4], NULL);
            _exit(1);
        } else if (WEXITSTATUS(status) != 0) {
            execlp(argv[4], argv[4], NULL);
            _exit(1);
        }
    }
    if (fork() == 0) {
        close(fd2[1]);
        dup2(fd2[0], 0);
        close(fd2[0]);
        execlp(argv[5], argv[5], NULL);
        _exit(1);
    }
    close(fd1[0]);
    close(fd1[1]);
    close(fd2[1]);
    close(fd2[0]);
    wait(0);
    wait(0);
    wait(0);
    _exit(0);

}