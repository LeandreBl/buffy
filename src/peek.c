#include <string.h>
#include "buffy.h"

ssize_t buffy_peek(struct buffy *buffy, void *data, size_t size)
{
    if (buffy->size < size) {
        size = buffy->size;
    }
    memcpy(data, buffy->data, size);
    return size;
}