#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/file.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/types.h>
#define len_str 6

int main(int argc, char **argv) {
    if (argc < 2) {
        return 0;
    }
    int f;
    if ((f = open(argv[1], O_RDWR | O_CREAT, 0777)) == -1) {
        return 0;
    }

    int flag = 0, target_pid, fd[3];
    char c, *str;
    pipe(fd);

    int p = fork();

    if(p == 0){//son
        int cnt = 0;
            read(fd[0], f1, 4);
            read(fd[1], str, len_str);
            read(fd[2], c, 4);
            int i = 0;
            while(i != strlen(str)){
                if(str[i] == c){
                    cnt ++;
                }
            }
            fputc('0' + cnt, f1);
            fputc('\n', f1);
    }
    else{
        int i = 0;
        str = malloc(len_str);
        while (!feof(stdin)) {
            scanf("%c\n", &str[i]);
            i++;
        }
        str[i] = '\n';
        fputs(str, f1);
        write(fd[0], f1, 4);
        write(fd[1], str, len_str);
        write(fd[2], c, 4);
    }
    fclose(f1);
    free(str);
    return 0;
}