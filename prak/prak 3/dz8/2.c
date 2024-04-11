// 2.
// Для тестирования написать программу, 
// которая получает в командной строке число N и 
// выводит на экран свой pid N раз. 
// Сделать 3 варианта завершения программы — 
// exit (0), exit(1), abort() и создать 3 исполняемых файла соответственно.



// Программа. В командной строке передаются имена 
// 2-ух исполняемых файлов, для каждого по 1 параметру, 
// а также символ p или s — определяет способ запуска.

// p) Запустить эти программы с использованием 
// передачи данных в виде списка на параллельное исполнение 
// (т.е. работают одновременно). При N = 30-50 должно 
// быть видно перемешивание вывода.

// s) Запустить эти программы 
// (переданные в командной строке) 
// с использованием векторной передачи данных 
// на последовательное исполнение (работают строго одна после другой).

// Определить с помощью макросов, 
// как завершились запущенные программы, 
// вывести эту информацию на экран (успешно ли 
// (т.е. по exit), что вернул exit, по какому сигналу).

// По окончании работы не должно остаться процессов «зомби».

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <string.h>

int main(int argc, char **argv)
{
    if (argc != 6) {fprintf(stderr, "wrong0");}
    int st;
    int n;
    pid_t pid; 
    pid_t pid1;
    if (strcmp(argv[5], "p") == 0)
    {
        if ((pid = fork()) < 0) {fprintf(stderr, "WRONG1");}

        else if (pid == 0)
        {
            execl(argv[1], argv[1], argv[2], NULL);
            fprintf(stderr, "WRONG2");
            exit(1);
        }
        else 
        {
            if ((pid1 = fork()) < 0) {fprintf(stderr, "WRONG1");}

            else if (pid1 == 0)
            {
                execl(argv[3], argv[3], argv[4], NULL);
                fprintf(stderr, "WRONG3");
                exit(1);
            }
            waitpid(pid,&st,0);
            if (WIFEXITED(st)) printf("%d\n", WEXITSTATUS(st));
            else if (WIFSIGNALED(st))  printf("%d\n", WTERMSIG(st));
            waitpid(pid1,&st,0);
            if (WIFEXITED(st)) printf("%d\n", WEXITSTATUS(st));
            else if (WIFSIGNALED(st)) printf("%d\n", WTERMSIG(st));
        }
    }
    else if (strcmp(argv[5], "s") == 0)
    {
        if ((pid = fork()) < 0) {fprintf(stderr, "WRONG11");}

        else if (pid == 0)
        {
            execl(argv[1], argv[1], argv[2], NULL);
            fprintf(stderr, "WRONG22"); exit(1);
        }
        else 
        {
            waitpid(pid,&st,0);
            if (WIFEXITED(st)) printf("%d\n", WEXITSTATUS(st));
            else if (WIFSIGNALED(st)) printf("%d\n", WTERMSIG(st));

            if ((pid1 = fork()) < 0) {fprintf(stderr, "WRONG1");}

            else if (pid1 == 0)
            {
                execl(argv[3], argv[3], argv[4], NULL);
                fprintf(stderr, "WRONG3");
                exit(1);
            }
            waitpid(pid1,&st,0);
            if (WIFEXITED(st)) printf("%d\n", WEXITSTATUS(st)); //если exit
            else if (WIFSIGNALED(st)) printf("%d\n", WTERMSIG(st)); // если abort
        }
    }
}