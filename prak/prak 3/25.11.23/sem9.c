#include<stdlib.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>
#include<string.h>
#include<stdio.h>
#include <signal.h>
#include <sys/stat.h>
#include <sys/types.h>	
#include <fcntl.h>

#define MAXLEN 256

pid_t p1, p2;
char buf;
char byt;

void handler(int sig){
    signal(SIGALRM, handler);
    return;
}
void sent0(int sig){
    signal(SIGUSR1,sent0);
    byt=0;
}
void sent1(int sig){
    signal(SIGUSR2,sent1);
    byt=1;
}

int main(int argc, char** argv){
    int fd=open(argv[1],O_RDONLY);
    signal(SIGALRM, handler);
    if ((p1=fork())<0){
            exit(1);
        }
    if(p1==0){//son1
        signal(SIGUSR1,sent0);
        signal(SIGUSR2,sent1);
        int count=0;
        char p=0;
        while (1) {   
            pause();
            count++;
            //printf("byt%d\n", byt);
            //printf("count%d\n", count);
            p<<=1;
            p+=byt;
            if (count==8){
                printf("%c\n", p);
                count=0;
                p=0;
            }
        //printf("get\n");
        kill(p2,SIGALRM);
        } 
    }
    if ((p2=fork())<0){
             exit(1);
         }
    if(p2==0){//son2
        signal(SIGALRM, handler);
        int res, i;
        while ((res = read(fd, &buf, sizeof(char))) > 0){
            for (i = 0; i < 8; i++)
            {
                //printf("sent%d\n", buf%2);
                if (buf%2){//1
                    kill(p1,SIGUSR2);
                }
                else {//0
                    kill(p1,SIGUSR1);
                }
                buf>>=1;
                pause();
            }
        }
        kill(p1, SIGIO);
        exit(0);
    }

    //father
    else{
        int status1, status2;
        wait(&status1);
        wait(&status2);
        

    }
    return 0;
}
