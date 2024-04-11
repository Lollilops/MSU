#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main(int argc, char ** argv)
{
    write(1, "OK", 2);
    return 0;
}