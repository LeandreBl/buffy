#include <criterion/criterion.h>
#include <errno.h>
#include "buffy.h"

Test(buffy, fixed_buffer_destroy)
{
    struct buffy buffer;
    size_t capacity = 10;

    cr_assert_eq(buffy_create(&buffer, capacity, BUFFY_FIXED_SIZE_STRATEGY), 0);
    cr_assert(buffer.data != NULL);
    cr_assert(buffer.capacity >= capacity);
    cr_assert(buffer.size == 0);
    cr_assert(buffer.flags == BUFFY_FIXED_SIZE_STRATEGY);
    buffy_destroy(&buffer);
    cr_assert(buffer.data == NULL);
    cr_assert(buffer.capacity == 0);
    cr_assert(buffer.size == 0);
    cr_assert(buffer.flags == 0);
}

Test(buffy, empty_fixed_buffer_destroy)
{
    struct buffy buffer;
    size_t capacity = 0;

    cr_assert_eq(buffy_create(&buffer, capacity, BUFFY_FIXED_SIZE_STRATEGY), 0);
    cr_assert(buffer.data != NULL);
    cr_assert(buffer.capacity >= capacity);
    cr_assert(buffer.size == 0);
    cr_assert(buffer.flags == BUFFY_FIXED_SIZE_STRATEGY);
    buffy_destroy(&buffer);
    cr_assert(buffer.data == NULL);
    cr_assert(buffer.capacity == 0);
    cr_assert(buffer.size == 0);
    cr_assert(buffer.flags == 0);
}

Test(buffy, dynamic_buffer_destroy)
{
    struct buffy buffer;
    size_t capacity = 10;

    cr_assert_eq(buffy_create(&buffer, capacity, BUFFY_DYNAMIC_SIZE_STRATEGY), 0);
    cr_assert(buffer.data != NULL);
    cr_assert(buffer.capacity >= capacity);
    cr_assert(buffer.size == 0);
    cr_assert(buffer.flags == BUFFY_DYNAMIC_SIZE_STRATEGY);
    buffy_destroy(&buffer);
    cr_assert(buffer.data == NULL);
    cr_assert(buffer.capacity == 0);
    cr_assert(buffer.size == 0);
    cr_assert(buffer.flags == 0);
}

Test(buffy, empty_dynamic_buffer_destroy)
{
    struct buffy buffer;
    size_t capacity = 0;

    cr_assert_eq(buffy_create(&buffer, capacity, BUFFY_DYNAMIC_SIZE_STRATEGY), 0);
    cr_assert(buffer.data != NULL);
    cr_assert(buffer.capacity >= capacity);
    cr_assert(buffer.size == 0);
    cr_assert(buffer.flags == BUFFY_DYNAMIC_SIZE_STRATEGY);
    buffy_destroy(&buffer);
    cr_assert(buffer.data == NULL);
    cr_assert(buffer.capacity == 0);
    cr_assert(buffer.size == 0);
    cr_assert(buffer.flags == 0);
}