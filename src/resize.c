#include <stdlib.h>
#include <errno.h>
#include "buffy.h"

int buffy_resize_capacity(struct buffy *buffy, size_t size)
{
    uint8_t *tmp;

    if (buffy->flags == BUFFY_FIXED_SIZE_STRATEGY) {
        errno = EPERM;
        return -1;
    }
    if (buffy->capacity == size) {
        return 0;
    }
    if (size == 0) {
        free(buffy->data);
        buffy->data = NULL;
        buffy->capacity = 0;
        return 0;
    }
    tmp = realloc(buffy->data, size);
    if (tmp == NULL) {
        return -1;
    }
    buffy->data = tmp;
    buffy->capacity = size;
    if (buffy->size > size) {
        buffy->size = size;
    }
    return 0;
}