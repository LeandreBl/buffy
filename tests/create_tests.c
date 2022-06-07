#include <criterion/criterion.h>
#include <errno.h>
#include "buffy.h"

Test(buffy, create_fixed_array)
{
    struct buffy buffer;
    size_t capacity = 10;

    cr_assert_eq(buffy_create(&buffer, capacity, BUFFY_FIXED_SIZE_STRATEGY), 0);
    cr_assert(buffer.data != NULL);
    cr_assert(buffer.capacity >= capacity);
    cr_assert(buffer.size == 0);
    cr_assert(buffer.flags == BUFFY_FIXED_SIZE_STRATEGY);
}

Test(buffy, create_invalid_strategy_array)
{
    struct buffy buffer;
    size_t capacity = 10;

    cr_assert_eq(buffy_create(&buffer, capacity, (enum buffy_allocation_strategy)42), -1);
    cr_assert_eq(errno, EINVAL);
}

Test(buffy, create_dynamic_array)
{
    struct buffy buffer;
    size_t capacity = 10;

    cr_assert_eq(buffy_create(&buffer, capacity, BUFFY_DYNAMIC_SIZE_STRATEGY), 0);
    cr_assert(buffer.data != NULL);
    cr_assert(buffer.capacity >= capacity);
    cr_assert(buffer.size == 0);
    cr_assert(buffer.flags == BUFFY_DYNAMIC_SIZE_STRATEGY);
}

Test(buffy, create_empty_fixed_array)
{
    struct buffy buffer;
    size_t capacity = 0;

    cr_assert_eq(buffy_create(&buffer, capacity, BUFFY_FIXED_SIZE_STRATEGY), 0);
    cr_assert(buffer.capacity >= capacity);
    cr_assert(buffer.size == 0);
    cr_assert(buffer.flags == BUFFY_FIXED_SIZE_STRATEGY);
}

Test(buffy, create_empty_dynamic_array)
{
    struct buffy buffer;
    size_t capacity = 0;

    cr_assert_eq(buffy_create(&buffer, capacity, BUFFY_DYNAMIC_SIZE_STRATEGY), 0);
    cr_assert(buffer.capacity >= capacity);
    cr_assert(buffer.size == 0);
    cr_assert(buffer.flags == BUFFY_DYNAMIC_SIZE_STRATEGY);
}