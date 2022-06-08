#include <criterion/criterion.h>
#include <errno.h>
#include "buffy.h"

Test(buffy, resize_capacity_from_empty_fixed_buffer)
{
    struct buffy buffer;
    size_t capacity = 0;

    cr_assert_eq(buffy_create(&buffer, capacity, BUFFY_FIXED_SIZE_STRATEGY), 0);
    cr_assert_eq(buffy_resize_capacity(&buffer, 10), -1);
    cr_assert_eq(errno, EPERM);
}

Test(buffer, resize_capacity_from_empty_dynamic_buffer)
{
    struct buffy buffer;
    size_t capacity = 0;

    cr_assert_eq(buffy_create(&buffer, capacity, BUFFY_DYNAMIC_SIZE_STRATEGY), 0);
    cr_assert_eq(buffy_resize_capacity(&buffer, 10), 0);
    cr_assert_eq(buffer.capacity, 10);
}

Test(buffer, resize_capacity_from_dynamic_buffer)
{
    struct buffy buffer;
    size_t capacity = 10;
    char letter = 'a';

    cr_assert_eq(buffy_create(&buffer, capacity, BUFFY_DYNAMIC_SIZE_STRATEGY), 0);
    for (size_t i = 0; i < 1000; i++) {
        letter = 'a' + i % ('z' - 'a');
        cr_assert_eq(buffy_write(&buffer, &letter, 1), 1);
        cr_assert(buffer.size == i + 1);
        cr_assert(buffer.capacity >= i + 1);
    }
    cr_assert_eq(buffy_resize_capacity(&buffer, 10), 0);
    cr_assert_eq(buffer.capacity, 10);
    cr_assert_eq(buffer.size, 10);
}

Test(buffer, resize_capacity_from_dynamic_buffer_to_zero)
{
    struct buffy buffer;
    size_t capacity = 10;
    char letter = 'a';

    cr_assert_eq(buffy_create(&buffer, capacity, BUFFY_DYNAMIC_SIZE_STRATEGY), 0);
    for (size_t i = 0; i < 1000; i++) {
        letter = 'a' + i % ('z' - 'a');
        cr_assert_eq(buffy_write(&buffer, &letter, 1), 1);
        cr_assert(buffer.size == i + 1);
        cr_assert(buffer.capacity >= i + 1);
    }
    cr_assert_eq(buffy_resize_capacity(&buffer, 0), 0);
    cr_assert_eq(buffer.capacity, 0);
    cr_assert_eq(buffer.size, 0);
}

Test(buffer, multiple_resize_read_writes)
{
    struct buffy buffer;
    size_t capacity = 10;
    const char *str = "Hello World!";
    size_t size = strlen(str);
    char letter;

    cr_assert_eq(buffy_create(&buffer, capacity, BUFFY_DYNAMIC_SIZE_STRATEGY), 0);
    cr_assert_eq(buffy_write(&buffer, str, size), size);
    cr_assert_eq(buffy_resize_capacity(&buffer, 4), 0);
    cr_assert_eq(buffer.capacity, 4);
    cr_assert_eq(buffer.size, 4);
    for (size_t i = 0; i < 4; i++) {
        cr_assert_eq(buffy_read(&buffer, &letter, 1), 1);
        cr_assert(buffer.size == 4 - i - 1);
        cr_assert(buffer.capacity >= 4 - i);
        cr_assert(letter == str[i]);
    }
    cr_assert_eq(buffy_resize_capacity(&buffer, 20), 0);
    cr_assert_eq(buffer.capacity, 20);
    cr_assert_eq(buffer.size, 0);
    cr_assert_eq(buffy_write(&buffer, str, size), size);
    cr_assert_eq(buffy_write(&buffer, str, size), size);
    cr_assert_eq(buffer.size, size * 2);
}