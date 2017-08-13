#include "apue.h"

ssize_t readn(int fd, void *ptr, size_t n) 
{
    size_t total = 0;
    size_t nleft = n;
    while (nleft > 0 && (total = read(fd, ptr, nleft)) > 0) {
        if (total == 0) {
            break;
        }
        nleft -= total;
        ptr += total;
    }

    return total; 
}

