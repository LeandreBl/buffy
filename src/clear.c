#include <errno.h>
#include "buffy.h"

void buffy_clear(struct buffy *buffy)
{
    buffy->size = 0;
}