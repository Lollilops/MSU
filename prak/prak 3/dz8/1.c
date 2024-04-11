// 1) для каждого содержащегося в каталоге файла-символьной_ссылки вывести имя файла,
//  на который она ссылается (по желанию можно пройти до конца, если окажется ссылкой на ссылку).

// Создать символьную ссылку ln -s filename fsymlinkname

// Читать из символьной ссылки см. функцию readlink.

// 2) если в каталоге есть подкаталоги, рекурсивно обойти все подкаталоги 
// (для всех уровней вложенности) и вывести на экран имена 
// содержащихся в них исполняемых файлов ( только тех, для которых и пользователь,
//  и группа (оба одновременно) имеют право на исполнение файла). 
// Функцию смены каталога chdir не использовать.

// Если для тестирования потребуется сменить или установить права доступа для файла, 
// используйте команду chmod.

// Обратите внимание, что при обращении к функции stat/lstat 
// нужно дополнить полученное имя так, чтобы оно указывало на файл из соответствующего каталога.
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <linux/limits.h>

void rec_dir(char *path)
{
    char filename[PATH_MAX];

    DIR *dir;
    dir = opendir(path); 
    if (dir == NULL) return;
    
    struct dirent *dirinfo;
    struct stat file_info;

    while ((dirinfo = readdir(dir)) != NULL) 
    {
        if ((strcmp(dirinfo -> d_name, ".") != 0) && (strcmp(dirinfo -> d_name, "..") != 0))
        {   
            sprintf(filename, "%s/%s", path, dirinfo -> d_name);
            if (lstat(filename, &file_info) == -1) {perror("l_stat"); continue;}

            if ((file_info.st_mode & S_IFMT) == S_IFDIR) {rec_dir(filename);}

            else{
                    // printf("%s",dirinfo->d_name);
                    // if(file_info.st_mode & S_IXUSR){
                    //     printf(" 1");
                    // }
                    // else printf(" 0");
                    // if (file_info.st_mode & S_IXGRP){
                    //     printf(" 1\n");
                    // }
                    // else printf(" 0\n");
                    if((file_info.st_mode & S_IXUSR) && (file_info.st_mode & S_IXGRP))
                {
                    printf("%s\n", dirinfo -> d_name);
                }
            }
        }
    }
    closedir(dir);
}

int main()
{
    char buf[255];

    printf("Ссылки:\n");

    DIR *dir; 
    dir = opendir(".");
    if (dir == NULL) {perror("opendir"); return -1;}

    struct dirent *fddir;
    struct stat file_info; 

    while(fddir = readdir(dir))
    {
        lstat(fddir -> d_name, &file_info); 
        if ((file_info.st_mode & S_IFMT) == S_IFLNK) 
        {
            if(readlink(fddir -> d_name, buf, sizeof(buf))) printf("%s\n", buf);
        }
    } 
    closedir(dir);

    printf("Файлы:\n");

    char start[PATH_MAX] = ".";

    rec_dir(start); 

    return 0;
}
