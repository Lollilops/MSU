#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <signal.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <time.h>

void print_proc(char game_mas[]){
    // int game_mas[9]={0, 0, 0, 0, 0, 0, 0, 0, 0};
    system("clear");
    for(int i = 1; i < 10; i++){
        if(game_mas[i] == '0'){
            printf("   ");
        }
        else if(game_mas[i] == '1'){
            printf(" X ");
        }
        else if(game_mas[i] == '2'){
            printf(" O ");
        }
        if(i != 9){
            if(i % 3 == 0){
                printf("\n-----------\n");
            }
            else{
                printf("|");
            }
        }
        else{
            printf("\n");
        }
    }
    // printf("nnnnn\n");
}

char prov_prok(char game_mas[]){
    int flag = 2;
    for(int i = 1; i<10; i++){
        if(game_mas[i] == '0'){
            flag = 0;
            break;
        }
    }
    for(int i = 1; i < 4; i+=3){
        if(game_mas[i] == game_mas[i+1] && game_mas[i+1] == game_mas[i+2] && game_mas[i] != '0'){
            return 1;
        }
    }
    for(int i = 1; i < 4; i++){
        if(game_mas[i] == game_mas[i+3] && game_mas[i+3] == game_mas[i+6] && game_mas[i] != '0'){
            return 1;
        }
    }
    if(game_mas[1] == game_mas[5] && game_mas[5] == game_mas[9] && game_mas[1] != '0'){
        return 1;
    }
    if(game_mas[3] == game_mas[5] && game_mas[5] == game_mas[7] && game_mas[3] != '0'){
        return 1;
    }
    return flag;
}

int main(){
    // int game_mas[9]={0, 0, 0, 0, 0, 0, 0, 0, 0};
    // printt_proc(game_mas);
    key_t key;
	int semid, shmid, game_ind;
	struct sembuf sops;
	char *shmaddr;
	char str[10]="0000000000";
	key = ftok("/tmp/shmem.txt", 'S');
	semid = semget(key, 1, 0666 | IPC_CREAT);
	shmid = shmget(key, 10, 0666 | IPC_CREAT);
	shmaddr = shmat(shmid, NULL, 0); 
    semctl(semid, 0, SETVAL, (int) 0);
    sops.sem_num = 0;
    sops.sem_flg = 0;
    do 
    {
        print_proc(str);
        while(!((game_ind > -1 && game_ind < 9) && str[game_ind + 1] == '0')){
            printf("Введите индекс поля(от 0 до 8):\n");
            scanf("%d", &game_ind);
            if(!((game_ind > -1 && game_ind < 9) && str[game_ind + 1] == '0')){
                printf("Введен неправильный индекс/поле занято!\n");
            }
        }
        str[game_ind + 1] = '1';
        print_proc(str);
        if(prov_prok(str) == 2) str[0] = '1';
        if(prov_prok(str) == 1){
            str[0] = '1';
            // break;
        }
        // if (fgets(str, 10, stdin) == NULL){
        //     strcpy(str, "Q"); 
        // }
        // printf("NNNNNNNNNNNNNNNNNN\n");
        // начало ввода
        // if((game_ind < 0 || game_ind > 9) && str[game_ind + 1] == 0){
        //     printf("Ok\n");
        // }
        // конец ввода
        // printf("Переход к клиенту\n");
        // for(int i = 0; i <10; i++){
        //     printf("%d\n", shmaddr[i]);
        // }
        strcpy(shmaddr, str);
    	sops.sem_op = 3;
        semop(semid, &sops, 1); // переход к клиенту
        sops.sem_op = 0;
        semop(semid, &sops, 1); // возврат
        strcpy(str, shmaddr);
        // printf("Ok");
        print_proc(str);
    }
    while(str[0] != '1');
    shmdt(shmaddr);
    shmctl(shmid, IPC_RMID, NULL);
    semctl(semid, 0, IPC_RMID, (int) 0);
    printf("\nDone\n");
    return 0;
}