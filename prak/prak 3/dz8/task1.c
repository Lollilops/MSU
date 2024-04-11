#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/file.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
#include <dirent.h>

void search(char* directory) {
    DIR* d = opendir(directory);
    if (d == NULL) {
        printf("Ошибка открытия директории\n");
        return;
    }
    struct dirent* dr;
    struct stat file_info;
    char bufname[255];
    char buflink[255];
    mode_t rides;
    size_t x;
    while ((dr = readdir(d)) != NULL) {
        if (!strcmp (dr->d_name,".") || !strcmp(dr->d_name,"..")) {
            continue;
        }   
        strcpy(bufname, directory);
        strcat(bufname, "/");
        strcat(bufname, dr->d_name);
        if (lstat(bufname, &file_info) != -1) {
            rides = file_info.st_mode;
            if ((rides & S_IXUSR) && (rides & S_IXGRP)) {
                printf("Исполняемый файл %s\n", bufname);
            }
            if (S_ISLNK(file_info.st_mode)) {
                printf("%s ", bufname);
                x = readlink(bufname, buflink, 255);
                buflink[x] = '\0';
                printf(" -> %s\n", buflink);
            } else if (S_ISDIR(file_info.st_mode)) {
                search(bufname);
            }
        }
    }
    return;
}

int main() {
    search(".");
    return 0;
}