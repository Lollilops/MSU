#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#define NMAX 10

int next_step(char *str) {  //возвращает 0 если матрица полностью заполнена
    int i = rand()%NMAX;
    int j;
    for(j=0; j<NMAX; j++)
        if(str[j]==' ') break;
    if(j==NMAX) return 0;
    while (((str[i]=='X') ||
            (str[i]=='O'))) {
            i = rand()%NMAX;
        }
    str[i]='O';
    return 1;
}

int check_win(char *str) {
    printf("=============\n");
    printf("| %c | %c | %c |\n",str[0],str[1],str[2]);
    printf("| %c | %c | %c |\n",str[3],str[4],str[5]);
    printf("| %c | %c | %c |\n",str[6],str[7],str[8]);
    printf("=============\n");

    if (((str[0]=='O') && (str[1]=='O') && (str[2]=='O')) ||
     ((str[3]=='O') && (str[4]=='O') && (str[5]=='O')) ||
     ((str[6]=='O') && (str[7]=='O') && (str[8]=='O')) ||
     ((str[0]=='O') && (str[3]=='O') && (str[6]=='O')) ||
     ((str[1]=='O') && (str[4]=='O') && (str[7]=='O')) ||
     ((str[2]=='O') && (str[5]='O') && (str[8]=='O')) ||
     ((str[0]=='O') && (str[4]=='O') && (str[8]=='O')) ||
     ((str[2]=='O') && (str[4]=='O') && (str[6]=='O')))
    return 1;
return 0;
}


int main(int argc, char **argv){
    srand(time(NULL));
    key_t key;
    int semid, shmid;
    struct sembuf sops;
    char *shmaddr;
    char str[NMAX];
    key = ftok("/tmp/shmem.txt",'S');
    /* создаем тот же самый ключ */
    semid = semget(key, 1, 0666 | IPC_CREAT);
    shmid = shmget(key, NMAX, 0666 | IPC_CREAT);
    /* аналогично предыдущему процессу - инициализации
    ресурсов */
    shmaddr = shmat(shmid, NULL, 0);
    sops.sem_num = 0;
    sops.sem_flg = 0;
    /* запускаем цикл */
    do{
        printf("\nWaiting... \n"); /* ожидание на семафоре */
        sops.sem_op = -2;
        /* будем ожидать, пока “значение семафора” +
        ”значение sem_op” не станет положительным*/
        semop(semid, &sops, 1);
        /* теперь значение семафора равно 1 */
        strcpy(str, shmaddr); /* копируем строку из
        разд.памяти */
        /*критическая секция - работа с разделяемой памятью
        - в этот момент первый процесс к разделяемой памяти
        доступа не имеет*/
        if(next_step(str)==0) str[9]= 'Q';
        if(check_win(str)==1){
            str[9]= 'Q';
            //printf("O player-process won\n");
            break;
            }
        strcpy(shmaddr,str); /* копируем строку из
        разд.памяти */
        if (str[9] == 'Q'){
            /* завершение работы – освобождаем
            разделяемую память */
            shmdt(shmaddr);
        }
        /*после работы – обнулим семафор*/
        sops.sem_op=-1;
        semop(semid, &sops, 1);
    } while (str[9] != 'Q');
    printf("\nDone\n");
    return 0;
}