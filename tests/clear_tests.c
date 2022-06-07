#include <criterion/criterion.h>
#include <errno.h>
#include "buffy.h"

Test(buffy, clear_empty_fixed_buffer)
{
    struct buffy buffer;
    size_t capacity = 0;
    const char *data = "Hello, world!";
    size_t size = strlen(data);

    cr_assert_eq(buffy_create(&buffer, capacity, BUFFY_FIXED_SIZE_STRATEGY), 0);
    cr_assert(buffy_write(&buffer, data, size) == 0);
    buffy_clear(&buffer);
    cr_assert(buffer.size == 0);
    buffy_destroy(&buffer);
}

Test(buffy, clear_empty_dynamic_buffer)
{
    struct buffy buffer;
    size_t capacity = 0;
    const char *data = "Hello, world!";
    size_t size = strlen(data);

    cr_assert_eq(buffy_create(&buffer, capacity, BUFFY_DYNAMIC_SIZE_STRATEGY), 0);
    cr_assert((size_t)buffy_write(&buffer, data, size) == size);
    buffy_clear(&buffer);
    cr_assert(buffer.size == 0);
    buffy_destroy(&buffer);
}

Test(buffy, clear_fixed_buffer)
{
    struct buffy buffer;
    size_t capacity = 10;
    const char *data = "Hello, world!";
    size_t size = strlen(data);

    cr_assert_eq(buffy_create(&buffer, capacity, BUFFY_FIXED_SIZE_STRATEGY), 0);
    cr_assert((size_t)buffy_write(&buffer, data, size) == (size > capacity) ? capacity : size);
    buffy_clear(&buffer);
    cr_assert(buffer.size == 0);
    buffy_destroy(&buffer);
}

Test(buffy, clear_dynamic_buffer)
{
    struct buffy buffer;
    size_t capacity = 10;
    const char *data = "Hello, world!";
    size_t size = strlen(data);

    cr_assert_eq(buffy_create(&buffer, capacity, BUFFY_DYNAMIC_SIZE_STRATEGY), 0);
    cr_assert((size_t)buffy_write(&buffer, data, size) == size);
    buffy_clear(&buffer);
    cr_assert(buffer.size == 0);
    buffy_destroy(&buffer);
}