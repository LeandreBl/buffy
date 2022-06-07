#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include "buffy.h"

ssize_t buffy_write(struct buffy *buffy, const void *data, size_t size)
{
    if (buffy->size + size > buffy->capacity) {
        switch (buffy->flags) {
            case BUFFY_FIXED_SIZE_STRATEGY:
                size = buffy->capacity - buffy->size;
                break;
            case BUFFY_DYNAMIC_SIZE_STRATEGY:
                if (buffy_resize_capacity(buffy, buffy->capacity - buffy->size + size) == -1) {
                    return -1;
                }
                break;
            default:
                errno = EINVAL;
                return -1;
        }
    }
    memcpy(buffy->data + buffy->size, data, size);
    buffy->size += size;
    return size;
}