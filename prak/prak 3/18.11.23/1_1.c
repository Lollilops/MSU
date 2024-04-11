#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/file.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/types.h>
#define MAX_LEN 81

int main(int argc, char **argv) {
    if (argc < 2) {
        return 0;
    }
    int f;
    if ((f = open(argv[1], O_RDWR | O_CREAT, 0777)) == -1) {
        return 0;
    }
    
    int fd1[2];
    int fd2[2];
    
    pipe(fd1);
    pipe(fd2);
    
    char c;
    char space = ' ';
    char s[MAX_LEN];
    
    printf("Введите символ, а затем строку\n");
    int p = fork();

    if (p == 0) { //сыновий
        close(fd1[1]);
        while (read(fd1[0], &c, 1)) {
            int count = 0;
            char temp;
            while (read(fd1[0], &temp, 1) && temp != ' ')
                if (temp == c) {
                    count++; //считаем кол-во
                }
            sprintf(s, "%d\n", count);  //пишем кол-во в строку
            write(f, &space, 1); //пишем пробел в файл
            write(f, s, strlen(s)); //пишем кол-во в файл
            
            write(fd2[0], &space, 1); //пишем в отца что-то
        }
        close(fd1[0]);
        exit(0);
    } else { //отцовский
        close(fd1[0]);
        while (read(0, &c, 1) && c != '\0' && c != '\n' && read(fd2[1], &c, 1)) {
            char temp;
            if (!read(0, &temp, 1)) {
                break;
            }
            int i = 0;
            while (read(0, &temp, 1) && temp != '\n' && temp != '\0') { //читаем строку в s
                s[i] = temp;
                i++; //чтобы вставить \0 на нужное место
            }
            s[i] = '\0';
            
            if (strcmp(s, "exit") == 0) {
                break;
            } else {
                write(f, &c, 1); //пишем символ в файл
                write(f, &space, 1); //пишем пробел в файл
                write(f, s, i); //пишем строку в файл
                write(fd1[1], &c, 1); //символ в канал
                write(fd1[1], s, i); //строку в канал
                write(fd1[1], &space, 1); //пробел в канал
            }
            strcpy(s, "\0");
        }
        
        close(fd1[1]);
        close(f);
        wait(0);
    }
    
    return 0;
}