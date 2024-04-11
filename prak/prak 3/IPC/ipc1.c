#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <string.h>
#include <time.h>
#define NMAX 10

int next_step(char *str) {
    int i = rand()%NMAX;
    int j;
    for(j=0; j<NMAX; j++)
        if(str[j]==' ') break;
    if(j==NMAX) return 0;
    while (((str[i]=='X') ||
            (str[i]=='O'))) {
            i = rand()%NMAX;
        }
    str[i]='X';
    return 1;
}

int check_win(char *str) {
    printf("=============\n");
    printf("| %c | %c | %c |\n",str[0],str[1],str[2]);
    printf("| %c | %c | %c |\n",str[3],str[4],str[5]);
    printf("| %c | %c | %c |\n",str[6],str[7],str[8]);
    printf("=============\n");

    if (((str[0]=='X') && (str[1]=='X') && (str[2]=='X')) ||
     ((str[3]=='X') && (str[4]=='X') && (str[5]=='X')) ||
     ((str[6]=='X') && (str[7]=='X') && (str[8]=='X')) ||
     ((str[0]=='X') && (str[3]=='X') && (str[6]=='X')) ||
     ((str[1]=='X') && (str[4]=='X') && (str[7]=='X')) ||
     ((str[2]=='X') && (str[5]='X') && (str[8]=='X')) ||
     ((str[0]=='X') && (str[4]=='X') && (str[8]=='X')) ||
     ((str[2]=='X') && (str[4]=='X') && (str[6]=='X')))
    return 1;
return 0;
}

int main(int argc, char **argv){
    srand(time(NULL));
    key_t key;
    int semid, shmid;
    struct sembuf sops;
    char *shmaddr;
    char str[NMAX]="         ";
    key = ftok("/tmp/shmem.txt", 'S');
    /* создаем ключ */
    semid = semget(key, 1, 0666 | IPC_CREAT);
    /* создаем один семафор с определенными правами доступа
    */
    shmid = shmget(key, NMAX, 0666 | IPC_CREAT);
    /* создаем разделяемую память на 9 элементов */
    shmaddr = shmat(shmid, NULL, 0);
    /* подключаемся к разделу памяти, в shaddr –
    указатель на буфер с разделяемой памятью */
    semctl(semid,0,SETVAL, (int) 0);
    /* инициализируем семафор значением 0 */
    sops.sem_num = 0;
    sops.sem_flg = 0;
    do { /* запуск цикла */
        if(next_step(str)==0) str[9]= 'Q';
        if(check_win(str)==1){
            str[9]= 'Q';
            //printf("X process won\n");
            break;
        }
        /* в текущий момент семафор открыт для этого
        процесса */
        strcpy(shmaddr, str); /* копируем строку в разд. память */
        /* предоставляем второму процессу возможность войти
        */
        sops.sem_op = 3; /* увеличение семафора на 3 */
        semop(semid, &sops, 1);
        /* ждем, пока семафор будет открыт для 1го процесса
        - для следующей итерации цикла */
        sops.sem_op = 0; /* ожидание обнуления семафора */
        semop(semid, &sops, 1);
        strcpy(str, shmaddr); /* копируем строку из разд. памяти */
    } while (str[9] != 'Q');
    /* в данный момент второй процесс уже дочитал из
    разделяемой памяти и отключился от нее – можно ее
    удалять*/
    shmdt(shmaddr) ; /* отключаемся от разделяемой памяти */
    shmctl(shmid, IPC_RMID, NULL);
    /* уничтожаем разделяемую память */
    semctl(semid, 0, IPC_RMID, (int) 0);
    /* уничтожаем семафор */
    printf("\nDone\n");
    return 0;
}