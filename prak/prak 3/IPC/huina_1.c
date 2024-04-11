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
	int semid, shmid;
	struct sembuf sops;
	char *shmaddr;
	char str [NMAX];
	key = ftok ("/usr/ter/exmpl", 'p' );
	semid = semget(key, 1, 0666); 
	shmid = shmget(key, NMAX, 0666);
	shmaddr = shmat(shmid, NULL, 0);
	sops.sem_num = 0;
    	sops.sem_flg = 0;
	do	{
		printf( "Waiting… \n" );
		sops.sem_op = -2 ;
		semop (semid, &sops, 1);
		strcpy (str, shmaddr);
		if (str[0] == 'Q') 
			shmdt(shmaddr);
		printf ("Read from shared memory: %s\n", str);
		sops.sem_op = -1;
		semop ( semid, &sops, 1); 
	} while ( str [ 0 ] != 'Q' );
	return 0;
}