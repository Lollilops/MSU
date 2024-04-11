#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <string.h>
#include <sys/shm.h>
#define NMAX 256

int main ( int argc, char ** argv )
{ 	
	key_t key;
	int semid, shmid ;
	struct sembuf sops ;
	char * shmaddr ;
	char str [ NMAX ] ;
	key = ftok ("/usr/ter/exmpl", 'p') ;
	semid = semget ( key, 1, 0666 | IPC_CREAT | IPC_EXCL ) ;
	shmid = shmget ( key, NMAX, 0666 | IPC_CREAT | IPC_EXCL ) ;
	shmaddr = shmat(shmid, NULL, 0 ) ; 
    semctl ( semid, 0, SETVAL, (int) 0 ) ;
    sops . sem_num = 0 ;
    sops . sem_flg = 0 ;
    do 
    {
        printf("Введите строку:") ;
        if ( fgets ( str, NMAX, stdin ) == NULL ){
            strcpy( str, "Q"); 
        }
        strcpy ( shmaddr, str );
    	sops . sem_op = 3 ;
        semop ( semid, & sops, 1 );
        sops . sem_op = 0 ;
        semop ( semid, & sops, 1 ); 
    }
    while ( str [ 0 ] != 'Q' ) ;
    shmdt ( shmaddr ) ;
    shmctl ( shmid, IPC_RMID, 	NULL);
    semctl ( semid, 0, IPC_RMID, (int) 0) ; 
    return 0 ;
    }
