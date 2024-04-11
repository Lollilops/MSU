#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main(int argc, char ** argv)
{
    //int f1 = open("t1.txt", O_RDONLY);
    //dup2(f1, 0);
    char buf[50];
    memset(buf, 0, sizeof(buf));
    read(0, buf, sizeof(buf)); 
    write(1, buf, strlen(buf));
    return 0;
}