#include <string.h>
#include <stdlib.h>
#include "buffy.h"

void buffy_destroy(struct buffy *buffy)
{
    free(buffy->data);
    memset(buffy, 0, sizeof(*buffy));
}