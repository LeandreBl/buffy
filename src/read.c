#include <errno.h>
#include "buffy.h"
#include "lvector.h"

ssize_t buffy_read(struct buffy *buffy, void *data, size_t size)
{
    ssize_t rd = buffy_peek(buffy, data, size);

    if (rd <= 0) {
        return rd;
    }
    return buffy_discard(buffy, rd);
}