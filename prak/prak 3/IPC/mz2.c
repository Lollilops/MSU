#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <string.h>

int main(int argc, char **argv)
{
    if (argc != 5) {perror("ARGC"); return -1;}

    int f = open(argv[3], O_WRONLY | O_APPEND | O_CREAT, 0666);
    int n = atoi(argv[4]);

    key_t sem_key = ftok(argv[1], atoi(argv[2]));

    int semid = semget(sem_key, 3, IPC_CREAT | 0666);
    if (semid == -1) {perror("SEMID"); return -1;}

    struct sembuf st1;

    int pd = getpid();
    char str[50];

    for (int i = 0; i < n; i++)
    {
        st1.sem_num = 1;
        st1.sem_op = -1;
        semop(semid, &st1, 1);

        sprintf(str, "%d OK\n", pd);
        write(f, str, strlen(str));

        st1.sem_num = 2;
        st1.sem_op = 1;
        semop(semid, &st1, 1);
    }
    close(f);
    semctl(semid, 1, IPC_RMID, (int)0);
    return 0;
}