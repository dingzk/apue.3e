#include "apue.h"

ssize_t
writen(int fd, const void * ptr, size_t n)
{
    size_t nwriten = 0;
    size_t nleft = n;

    if (nleft > 0 ) {
        while (nwriten = write(fd, ptr, nleft) > 0) {
            if (nwriten == nleft) {
                break;
            } 
            nleft -= nwriten;
            ptr += nwriten;
        }
    }

    return n - nleft;
}
