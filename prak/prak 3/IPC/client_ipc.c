#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <string.h>
#include <signal.h>
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
    key_t key; 
	int semid, shmid, game_ind;
	struct sembuf sops;
	char *shmaddr;
	char str [10];
	key = ftok ("/tmp/shmem.txt",'S');
	semid = semget(key, 1, 0666 | IPC_CREAT); 
	shmid = shmget(key, 10, 0666 | IPC_CREAT);
	shmaddr = shmat(shmid, NULL, 0);
	sops.sem_num = 0;
    sops.sem_flg = 0;
	do{
		printf( "Waiting… \n" );
		sops.sem_op = -2;
		semop(semid, &sops, 1); // принятие
		strcpy(str, shmaddr);
        print_proc(str);
        if(prov_prok(str) == 1){
            str[0] = '1';
            sops.sem_op = -1;
		    semop(semid, &sops, 1);
            break;
        }
        if(prov_prok(str) == 2){
            str[0] = '1';
            sops.sem_op = -1;
		    semop(semid, &sops, 1);
            break;
        }
        // for(int i = 0; i <10; i++){
        //     printf("%d\n", shmaddr[i]);
        // }
        // if (str[0] == '1')
		// 	shmdt(shmaddr);
        //     sops.sem_op = -1;
		//     semop(semid, &sops, 1);
            // break;
        // printf("\n");
        // for(int i = 0; i <10; i++){
        //     printf("%d", shmaddr[i]);
        // }
        // printf("\n");
        // printf("%d\n", str[0]);
        game_ind = -1;
        while(!((game_ind > -1 && game_ind < 9) && str[game_ind + 1] == '0')){
            printf("Введите индекс поля(от 0 до 8):\n");
            scanf("%d", &game_ind);
            if(!((game_ind > -1 && game_ind < 9) && str[game_ind + 1] == '0')){
                printf("Введен неправильный индекс/поле занято!\n");
                // printf("%d %d", game_ind, str[game_ind + 1]);
            }
        }
        str[game_ind + 1] = '2';
        print_proc(str);
        if(prov_prok(str) == 2) str[0] = '1';
        if(prov_prok(str) == 1){
            str[0] = '1';
            // break;
        }
        strcpy(shmaddr,str);
        if (str[0] == '1')
			shmdt(shmaddr);
		sops.sem_op = -1;
		semop(semid, &sops, 1); // отдача
		// printf ("Read from shared memory: %s\n", str);// добавить разбиение на массив
	} while(str[0] != '1');
    printf("\nDone\n");
	return 0;
}