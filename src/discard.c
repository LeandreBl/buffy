#include <string.h>
#include "buffy.h"

size_t buffy_discard(struct buffy *buffy, size_t size)
{
    if (size == 0) {
        return 0;
    }
    if (buffy->size < size) {
        size = buffy->size;
    }
    memmove(buffy->data, buffy->data + size, buffy->size - size);
    buffy->size -= size;
    return size;
}