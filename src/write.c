#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include "buffy.h"

#define MAX(a, b) (a > b ? a : b)

ssize_t buffy_write(struct buffy *buffy, const void *data, size_t size)
{
    size_t newsize;

    if (buffy->size + size > buffy->capacity) {
        if (buffy->flags == BUFFY_FIXED_SIZE_STRATEGY) {
            errno = ENOBUFS;
            return -1;
        }
        newsize = MAX(1, buffy->capacity * 2);
        buffy->data = realloc(buffy->data, newsize);
        if (buffy->data == NULL) {
            return -1;
        }
        buffy->capacity = newsize;
    }
    memcpy(buffy->data + buffy->size, data, size);
    buffy->size += size;
    return size;
}