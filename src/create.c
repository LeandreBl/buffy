#include <errno.h>
#include <stdlib.h>
#include <assert.h>
#include "buffy.h"

int buffy_create(struct buffy *buffy, size_t capacity, enum buffy_allocation_strategy flags)
{
    switch (flags) {
        default:
            errno = EINVAL;
            return -1;
        case BUFFY_DYNAMIC_SIZE_STRATEGY:
        case BUFFY_FIXED_SIZE_STRATEGY:
            break;
    }
    buffy->data = malloc(capacity);
    if (buffy->data == NULL) {
        return -1;
    }
    buffy->capacity = capacity;
    buffy->size = 0;
    buffy->flags = flags;
    return 0;
}