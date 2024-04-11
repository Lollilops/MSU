#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

int main(int argc, char **argv)
{
    if (argc != 5) {perror("ARGC"); return -1;}

    FILE *f = fopen(argv[3], "w+");
    if (f == NULL) {perror("FILE"); return -1;}

    int n = atoi(argv[4]);

    key_t sem_key = ftok(argv[1], atoi(argv[2]));
    if (sem_key == -1) {perror("SEMKEY"); return -1;}
    int semid = semget(sem_key, 3, IPC_CREAT | 0666);
    if (semid == -1) {perror("SEMID"); return -1;}

    struct sembuf st1; 

    semctl(semid, 0, SETVAL, 1);
    semctl(semid, 1, SETVAL, 0);
    semctl(semid, 2, SETVAL, 0);

    char s[30];

    for (int i = 0; i < n; i++)
    {
        st1.sem_num = 2;
        st1.sem_op = -1;
        semop(semid, &st1, 1);

        fgets(s, sizeof(s), f);
        printf("%s", s);

        st1.sem_num = 0;
        st1.sem_op = 1;
        semop(semid, &st1, 1);
    }
    fclose(f);
    semctl(semid, 2, IPC_RMID, (int)0);
    return 0;
}