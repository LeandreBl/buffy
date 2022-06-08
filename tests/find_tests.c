#include <criterion/criterion.h>
#include <errno.h>
#include "buffy.h"

Test(buffy, find_in_empty_buffer)
{
    struct buffy buffer;
    size_t capacity = 0;
    const char *data = "Hello, world!";
    size_t size = strlen(data);

    cr_assert_eq(buffy_create(&buffer, capacity, BUFFY_FIXED_SIZE_STRATEGY), 0);
    cr_assert(buffy_find(&buffer, data, size) == -1);
}

Test(buffy, find_in_correct_buffer)
{
    struct buffy buffer;
    size_t capacity = 0;
    const char *data = "Hello, world!";
    size_t size = strlen(data);

    cr_assert_eq(buffy_create(&buffer, capacity, BUFFY_DYNAMIC_SIZE_STRATEGY), 0);
    cr_assert((size_t)buffy_write(&buffer, data, size) == size);
    cr_assert(buffy_find(&buffer, "Hell", 4) == 0);
    cr_assert(buffy_find(&buffer, "llo", 3) == 2);
    cr_assert(buffy_find(&buffer, "!", 1) == 12);
    cr_assert(buffy_find(&buffer, "Hello, world!", 13) == 0);
}

Test(buffy, tool_large_find_in_buffer)
{
    struct buffy buffer;
    size_t capacity = 0;
    const char *data = "Hello, world!";
    size_t size = strlen(data);

    cr_assert_eq(buffy_create(&buffer, capacity, BUFFY_DYNAMIC_SIZE_STRATEGY), 0);
    cr_assert((size_t)buffy_write(&buffer, data, size) == size);
    cr_assert(buffy_find(&buffer, "This is clearly a too long string", 33) == -1);
}

Test(buffy, find_in_buffer_with_intermediate_reads)
{
    struct buffy buffer;
    size_t capacity = 0;
    const char data[] = "Hello, world!";
    size_t size = strlen(data);
    char temp_buffer[sizeof(data)] = {0};

    cr_assert_eq(buffy_create(&buffer, capacity, BUFFY_DYNAMIC_SIZE_STRATEGY), 0);
    cr_assert((size_t)buffy_write(&buffer, data, size) == size);
    cr_assert(buffy_find(&buffer, "Hell", 4) == 0);
    cr_assert(buffy_read(&buffer, temp_buffer, 5) == 5);
    cr_assert(buffy_find(&buffer, ", world!", 8) == 0);
}