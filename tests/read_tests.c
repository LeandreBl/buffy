#include <criterion/criterion.h>
#include <errno.h>
#include "buffy.h"

Test(buffy, read_from_empty_buffer)
{
    struct buffy buffer;
    size_t capacity = 0;
    const char data[] = "Hello, world!";
    size_t size = strlen(data);
    char tmp_buffer[sizeof(data)] = {0};

    cr_assert_eq(buffy_create(&buffer, capacity, BUFFY_FIXED_SIZE_STRATEGY), 0);
    cr_assert_eq(buffy_read(&buffer, tmp_buffer, size), 0);
    cr_assert_eq(buffer.size, 0);
    cr_assert_eq(buffer.capacity, 0);
}

Test(buffy, read_from_too_short_buffer)
{
    struct buffy buffer;
    size_t capacity = 0;
    const char data[] = "Hello, world!";
    size_t size = strlen(data);
    char tmp_buffer[sizeof(data)] = {0};

    cr_assert_eq(buffy_create(&buffer, capacity, BUFFY_DYNAMIC_SIZE_STRATEGY), 0);
    cr_assert_eq(buffy_write(&buffer, data, size / 2), size / 2);
    cr_assert(buffer.size == size / 2);
    cr_assert(buffer.capacity >= size / 2);
    cr_assert_eq(buffy_read(&buffer, tmp_buffer, size), size / 2);
    cr_assert(buffer.size == 0);
}

Test(buffy, read_from_full_buffer)
{
    struct buffy buffer;
    char letter = 'a';

    cr_assert_eq(buffy_create(&buffer, 1000, BUFFY_DYNAMIC_SIZE_STRATEGY), 0);
    for (size_t i = 0; i < 1000; i++) {
        letter = 'a' + i % ('z' - 'a');
        cr_assert_eq(buffy_write(&buffer, &letter, 1), 1);
        cr_assert(buffer.size == i + 1);
        cr_assert(buffer.capacity >= i + 1);
    }
    for (size_t i = 0; i < 1000; i++) {
        cr_assert_eq(buffy_read(&buffer, &letter, 1), 1);
        cr_assert_eq(letter, 'a' + i % ('z' - 'a'));
        cr_assert(buffer.size == 1000 - i - 1);
        cr_assert(buffer.capacity >= 1000 - i - 1);
    }
}