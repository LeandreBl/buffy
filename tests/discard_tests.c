#include <criterion/criterion.h>
#include <errno.h>
#include "buffy.h"

Test(buffy, discard_filled_buffer)
{
    struct buffy buffer;
    const char str[] = "hello, world!";
    size_t size = strlen(str);
    char tmp_buffer[sizeof(str)] = {0};
    size_t capacity = 20;

    cr_assert_eq(buffy_create(&buffer, capacity, BUFFY_FIXED_SIZE_STRATEGY), 0);
    cr_assert_eq(buffy_write(&buffer, str, size), size);
    cr_assert_eq(buffy_discard(&buffer, 3), 3);
    cr_assert_eq(buffy_read(&buffer, tmp_buffer, size - 3), size - 3);
    cr_assert_eq(memcmp(tmp_buffer, str + 3, size - 3), 0);
}

Test(buffy, discard_empty_buffer)
{
    struct buffy buffer;

    cr_assert_eq(buffy_create(&buffer, 20, BUFFY_FIXED_SIZE_STRATEGY), 0);
    cr_assert_eq(buffy_discard(&buffer, 3), 0);
}