#define _GNU_SOURCE
#include <string.h>
#include "buffy.h"

ssize_t buffy_find(struct buffy *buffy, const void *data, size_t size)
{
    void *ptr = memmem(buffy->data, buffy->size, data, size);

    if (ptr == NULL) {
        return -1;
    }
    return (uint8_t *)ptr - buffy->data;
}