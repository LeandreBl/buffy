#include <errno.h>
#include "buffy.h"
#include "lvector.h"

ssize_t buffy_read(struct buffy *buffy, void *data, size_t size)
{
    ssize_t rd = buffy_peek(buffy, data, size);

    if (rd == -1) {
        return rd;
    }
    memmove(buffy->data, buffy->data + size, buffy->size - size);
    buffy->size -= size;
    return size;
}