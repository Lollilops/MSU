#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <string.h>
#include <errno.h>

typedef struct start_struct
{
    char word[50][255];
    char command[50][2];
    //int priority[50];
}s_s;

int i_main; //индекс word
pid_t pid_son;
s_s structura; //структура

void execution();
int f_and(int,int);
int f_file(int,int);
int f_pipe(int,int);
int exec(int,int,int);

int main()
{
    char start_str[255];
    char cmd[255];
    

    while(1)
    {
        i_main = 0;
        int i_cmd = 0; //индекс command
        int queue = 0; //приоритет выполнения
        int i = 0;    //индекс всей строки
        int max_queue = 0;

        for(int j = 0; j < 50; j++)
        {
            memset(structura.word[j], 0, sizeof(char)*255);
            memset(structura.command[j], 0, sizeof(char)*2);
            //memset(structura.priority, 0, sizeof(int)*50);
        }

        fgets(start_str, sizeof(start_str), stdin);
        int len_start = strlen(start_str);
        if (start_str[len_start - 1] == '\n') start_str[len_start - 1] = 0;
        if (!(strcmp(start_str, "exit"))) return 0;

        while (start_str[i] != 0)
        {            
            if ((start_str[i] == '&') && (start_str[i+1] == '&'))
            {
                structura.command[i_main][0] = start_str[i++]; //присвоется &
                structura.command[i_main][1] = start_str[i++]; //присвоется &
                i_main++;
                i_cmd = 0;
            }
            else if ((start_str[i] == '|') && (start_str[i+1] == '|'))
            {
                structura.command[i_main][0] = start_str[i++]; //присвоется |
                structura.command[i_main][1] = start_str[i++]; //присвоется |
                i_main++;
                i_cmd = 0;
            }
            else if ((start_str[i] == '>') && (start_str[i+1] == '>'))
            {
                structura.command[i_main][0] = start_str[i++]; //присвоется >
                structura.command[i_main][1] = start_str[i++]; //присвоется >
                i_main++;
                i_cmd = 0;
            }
            else
            {
                switch (start_str[i])
                {
                case '(':
                    queue++;
                    //structura.priority[i_main] = queue;
                    //if (queue > max_queue) max_queue = queue;
                    i++;
                    break;
                case ')':
                    //structura.priority[i_main] = queue;
                    queue--;
                    i++;
                    break;
                case '|':
                    structura.command[i_main][0] = start_str[i];
                    i_main++;
                    i_cmd = 0;
                    i++;
                    break;
                case '>':
                    structura.command[i_main][0] = start_str[i];
                    i_main++;
                    i_cmd = 0;
                    i++;
                    break;  
                case '<':
                    structura.command[i_main][0] = start_str[i];
                    i_main++;
                    i_cmd = 0;
                    i++;
                    break;
                case ';':
                    structura.command[i_main][0] = start_str[i];
                    i_main++;
                    i_cmd = 0;
                    i++;
                    break;    
                case '&':
                    structura.command[i_main][0] = start_str[i];
                    i_main++;
                    i_cmd = 0;
                    i++;
                    break;
                default:
                    structura.word[i_main][i_cmd++] = start_str[i++]; 
                    break;
                }
            }
        }
        execution();
    }
}

int f_and_or(int start, int end)
{
    int prev = 0;
    for (int i = start; i <= end; i++)
    {
        if(!strcmp(structura.command[i], "&&"))
        {
            if(f_file(prev, i)) //команды слева выполнились
            {
                prev = i + 1;
            }
            else {
                //не выполняем cmd после &&
            }
        }
        else if (!strcmp(structura.command[i], "||")) // команды слева не выполнились
        {
            if (!(f_file(prev, i)))
            {
                prev = i + 1;
            }
            else 
            {
                //не выполняем cmd после ||
            }
        }
    }
    return f_file(prev, end);
}

int f_file(int start, int end)
{
    int f;
    //разве тут нам не надо прев? или не может дважды встретиться запись в файл? 
    for(int i = start; i <= end; i++)
    {
        if(!strcmp(structura.command[i], ">>"))
        {
            f = open(structura.word[i+1], O_RDWR | O_APPEND); //+1 тк файл в след элем структуры 
            dup2(f, 1);
            return f_pipe(start, i);
        }
        else if(!strcmp(structura.command[i], ">"))
        {
            f = open(structura.word[i+1], O_WRONLY);
            dup2(f, 1);
            return f_pipe(start, i+1);
        }
        else if(!strcmp(structura.command[i], "<"))
        {
            f = open(structura.word[i+1], O_RDONLY);
            dup2(f, 0);
            return f_pipe(start, i);
        }
    }
    //где проверка на несущ >> и сущ |
}

int f_pipe(int start, int end)
{
    int fd[2]; int prev[2]; //два канала
    prev[0] = 0; prev[1] = 1;
    int pid; int status;
    for (int i = start; i <= end; i++)
    {
        if (i == end)
        {
            pid = exec(i, prev[0], 0); // какую команду откуда считываем и записываем в stdin
            waitpid(pid, &status, NULL);
            if (!status) {return 1;} //команда выполнилась
            else {return 0;} 
        }
        pipe(fd);
        exec(i, prev[0], fd[1]);  //почему мы здесь не приравниваем к pid
        prev[0] = fd[0];
        prev[1] = fd[1];
    }
}

int exec(int i, int from, int to)
{
    dup2(from, 0); dup2(to, 1);

}

void execution()
{
    int i_execution = 0;
    int start = i_execution;
    int end; 
    for (i_execution = 0; i_execution < i_main; i_execution++)
    {
        if (!strcmp(structura.command[i_execution], "&"))
        {
            end = i_execution;
            pid_t pid_fon;
            if (!(pid_fon = fork())) //сын - фон
            {
                setpgrp();
                signal(SIGINT, SIG_IGN);
                int f_null = open("/dev/null", O_RDONLY);
                dup2(f_null, 0);
                if (f_and(start, end)){continue;}
                else {return 1;}
            }
            else
            {
                start = end + 1;
            }
        }
        else if (!strcmp(structura.command[i_execution], ";"))
        {
            end = i_execution;
            if (!(f_and_or(start, end))){return 1;} //если вернулся 0
            start = end + 1;
        }
    }
}