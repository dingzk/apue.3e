#include "apue.h"
#include <fcntl.h>
#include <sys/mman.h>

#define COPYINCR (1024*1024*1024)

int main(int argc, char **argv)
{
    int fdin, fdout;
    struct stat sbuf;
    void *src, *dst;
    off_t fsz = 0;
    size_t copysz;
    if (argc != 3) {
        printf("usage: %s <fromefile> <tofile>", *argv);
    } 
    if ((fdin = open(*(argv + 1), O_RDONLY)) < 0) {
        printf("open fdin error\n");
    }
    if ((fdout = open(*(argv + 2), O_CREAT|O_RDWR|O_TRUNC, FILE_MODE)) < 0) {
        printf("open fdout error\n");
    }
    if (fstat(fdin, &sbuf) < 0) {
       printf("fstat error\n"); 
    }
    if (ftruncate(fdout, sbuf.st_size) < 0)
        printf("ftruncate error\n");
    while (fsz < sbuf.st_size) {
        if ((sbuf.st_size - fsz) > COPYINCR)
            copysz = COPYINCR;
        else
            copysz = sbuf.st_size - fsz;
        src = mmap(NULL, copysz, PROT_READ, MAP_PRIVATE, fdin, fsz);
        if (src == MAP_FAILED)
            printf("mmap fdin error failed\n");
        dst = mmap(NULL, copysz, PROT_WRITE|PROT_READ, MAP_SHARED, fdout, fsz);
        if (dst == MAP_FAILED)
            printf("mmap fdout error failed\n");
        memcpy(dst, src, copysz);
        munmap(src, copysz);
        munmap(dst, copysz);
        fsz += copysz;
    }

    return 0;
}

