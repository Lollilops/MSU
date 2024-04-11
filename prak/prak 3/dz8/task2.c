#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/file.h>
#include <sys/wait.h>

void info_end(char* prog, int status) {
    if (WIFEXITED(status)){
            printf("%s завершилась exit со значением %d\n", prog, WEXITSTATUS(status));
        } 
    if (WIFSIGNALED(status)) {
        printf("%s завершилась по сигналу %d\n", prog, WTERMSIG(status));
    }
}


int main(int argc, char** argv) {
    if (argc != 6) {
        printf("Некорректные аргументы\n");
        return 1;
    }
    // пример вызова ./task2 test1.c 5 test2.c 10 p/s
    // char* prog1 = argv[1];
    // char* prog2 = argv[3];
    // int n1 = atoi(argv[2]);
    // int n2 = atoi(argv[4]);
    pid_t p1, p2;
    int status1, status2;
    int len1 = strlen(argv[1]) + 3;
    char name1[len1];
    strcpy(name1, "./");
    strcat(name1, argv[1]);
    int len2 = strlen(argv[3]) + 3;
    char name2[len2];
    strcpy(name2, "./");
    strcat(name2, argv[3]);
    printf("%s   %s \n", name1, name2);
    
    if (argv[5][0] == 'p') {
        if ((p1 = fork()) < 0) {
            printf("Error fork\n");
            exit(1);
        } else if (!p1) {
            execl(name1, name1, argv[2], NULL);
            printf("Error\n");
            exit(1);
        }
        if ((p2 = fork()) < 0) {
            printf("Error fork\n");
            exit(1);
        } else if (!p2) {
            execl(name2, name2, argv[4], NULL);
            printf("Error\n");
            exit(1);
        }
        wait(&status1);
        wait(&status2);
    } else if (argv[5][0] == 's') {
        char* argvprog1[] ={name1, argv[2], NULL};
        char* argvprog2[] ={name2, argv[4], NULL};
        if ((p1 = fork()) < 0) {
            printf("Error fork\n");
            exit(1);
        } else if (!p1) {
            execv(name1, argvprog1);
            printf("Error\n");
            exit(1);
        }
        wait(&status1);
        if ((p2 = fork()) < 0) {
            printf("Error fork\n");
            exit(1);
        } else if (!p2) {
            execv(name2, argvprog2);
            printf("Error\n");
            exit(1);
        }
        wait(&status2);

    } else {
        printf("Неверная опция\n");
        return 1;
    }
    wait(&status1);
    wait(&status2);
    info_end(argv[1], status1);
    info_end(argv[3], status2);
    return 0;
}