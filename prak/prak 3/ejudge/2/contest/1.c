#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int
main(int argc, char *argv[])
{
    if (argc < 3)
    return 0;

    int fd = open(argv[1], O_RDONLY);
    unsigned short base = (unsigned short) strtol(argv[2], NULL, 16);
    unsigned short v_addr, p_addr, page, offset, page_addr, info, buf;

    // char buf[2];
    // char f[3];

    while (scanf("%hx", &buf) == 1)
    {
        // v_addr = (unsigned short) strtol(buf, NULL, 16);
        v_addr = buf;
        page = v_addr >> 9;
        offset = v_addr & 0x1FF;

        lseek(fd, base + 2*page, SEEK_SET);
        read(fd, &page_addr, 2);            // получили физ адрес страницы
        // p_addr = (page_addr << 9) | offset;
        p_addr = page_addr | offset;
        lseek(fd, p_addr, SEEK_SET);
        read(fd, &info, 2);
        printf("%hu\n", info);
    }
    
    close(fd);
    return 0;
}