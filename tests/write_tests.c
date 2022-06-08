#include <criterion/criterion.h>
#include <errno.h>
#include "buffy.h"

Test(buffy, write_in_empty_fixed_buffer)
{
    struct buffy buffer;
    size_t capacity = 0;
    const char *data = "Hello, world!";
    size_t size = strlen(data);
    char letter;

    cr_assert_eq(buffy_create(&buffer, capacity, BUFFY_FIXED_SIZE_STRATEGY), 0);
    cr_assert(buffy_write(&buffer, data, size) == 0);
    cr_assert(buffer.size == 0);
    for (size_t i = 0; i < size; i++) {
        cr_assert(buffy_read(&buffer, &letter, 1) == 0);
    }
}

Test(buffy, write_in_empty_dynamic_buffer)
{
    struct buffy buffer;
    size_t capacity = 0;
    const char *data = "Hello, world!";
    size_t size = strlen(data);
    char letter;

    cr_assert_eq(buffy_create(&buffer, capacity, BUFFY_DYNAMIC_SIZE_STRATEGY), 0);
    cr_assert((size_t)buffy_write(&buffer, data, size) == size);
    cr_assert(buffer.size == size);
    cr_assert(buffer.capacity >= size);
    for (size_t i = 0; i < size; i++) {
        cr_assert(buffy_read(&buffer, &letter, 1) == 1);
        cr_assert(buffer.size == size - i - 1);
        cr_assert(letter == data[i]);
    }
}

Test(buffy, write_in_fixed_buffer)
{
    struct buffy buffer;
    size_t capacity = 10;
    const char *data = "Hello, world!";
    size_t size = strlen(data);
    char letter;

    cr_assert_eq(buffy_create(&buffer, capacity, BUFFY_FIXED_SIZE_STRATEGY), 0);
    cr_assert((size_t)buffy_write(&buffer, data, size) == capacity);
    cr_assert(buffer.size == capacity);
    cr_assert(buffer.capacity >= capacity);
    for (size_t i = 0; i < size; i++) {
        if (i < capacity) {
            cr_assert(buffy_read(&buffer, &letter, 1) == 1);
        } else {
            cr_assert(buffy_read(&buffer, &letter, 1) == 0);
        }
    }
}

Test(buffy, write_in_dynamic_buffer)
{
    struct buffy buffer;
    size_t capacity = 10;
    const char *data = "Hello, world!";
    size_t size = strlen(data);
    char letter;

    cr_assert_eq(buffy_create(&buffer, capacity, BUFFY_DYNAMIC_SIZE_STRATEGY), 0);
    cr_assert((size_t)buffy_write(&buffer, data, size) == size);
    cr_assert(buffer.size == size);
    cr_assert(buffer.capacity >= size);
    for (size_t i = 0; i < size; i++) {
        cr_assert(buffy_read(&buffer, &letter, 1) == 1);
        cr_assert(letter == data[i]);
    }
}

Test(buffy, multiple_write_in_fixed_buffer)
{
    struct buffy buffer;
    size_t capacity = 20;
    const char *data = "Hello, world!";
    size_t size = strlen(data);
    char letter;

    cr_assert_eq(buffy_create(&buffer, capacity, BUFFY_FIXED_SIZE_STRATEGY), 0);
    cr_assert((size_t)buffy_write(&buffer, data, size) == size);
    cr_assert(buffer.size == size);
    cr_assert(buffer.capacity >= size);
    cr_assert((size_t)buffy_write(&buffer, data, size) == capacity - size);
    cr_assert(buffer.size == capacity);
    cr_assert(buffer.capacity >= capacity);
    for (size_t i = 0; i < size * 2; i++) {
        if (i < capacity) {
            cr_assert(buffy_read(&buffer, &letter, 1) == 1);
        } else {
            cr_assert(buffy_read(&buffer, &letter, 1) == 0);
        }
    }
}

Test(buffy, multiple_write_in_dynamic_buffer)
{
    struct buffy buffer;
    size_t capacity = 20;
    const char *data = "Hello, world!";
    size_t size = strlen(data);
    char letter;

    cr_assert_eq(buffy_create(&buffer, capacity, BUFFY_DYNAMIC_SIZE_STRATEGY), 0);
    cr_assert((size_t)buffy_write(&buffer, data, size) == size);
    cr_assert(buffer.size == size);
    cr_assert(buffer.capacity >= size);
    cr_assert((size_t)buffy_write(&buffer, data, size) == size);
    cr_assert(buffer.size == size * 2);
    cr_assert(buffer.capacity >= size * 2);
    for (size_t i = 0; i < size * 2; i++) {
        cr_assert(buffy_read(&buffer, &letter, 1) == 1);
    }
}

Test(buffy, multiple_write_and_reads_in_fixed_buffer)
{
    struct buffy buffer;
    size_t capacity = 10;
    const char *data = "Hello, world!";
    size_t size = strlen(data);
    char letter;

    cr_assert_eq(buffy_create(&buffer, capacity, BUFFY_FIXED_SIZE_STRATEGY), 0);
    cr_assert((size_t)buffy_write(&buffer, data, size) == capacity);
    cr_assert(buffer.size == capacity);
    cr_assert(buffer.capacity >= capacity);
    for (size_t i = 0; i < capacity / 2; i++) {
        cr_assert(buffy_read(&buffer, &letter, 1) == 1);
    }
    cr_assert((size_t)buffy_write(&buffer, data, size) == capacity - capacity / 2);
    cr_assert(buffer.size == capacity);
    cr_assert(buffer.capacity >= capacity);
    for (size_t i = 0; i < size; i++) {
        if (i < capacity) {
            cr_assert(buffy_read(&buffer, &letter, 1) == 1);
        } else {
            cr_assert(buffy_read(&buffer, &letter, 1) == 0);
        }
    }
}

Test(buffy, empty_write_in_fixed_buffer)
{
    struct buffy buffer;
    size_t capacity = 10;
    char letter;

    cr_assert_eq(buffy_create(&buffer, capacity, BUFFY_FIXED_SIZE_STRATEGY), 0);
    cr_assert((size_t)buffy_write(&buffer, "", 0) == 0);
    cr_assert(buffer.size == 0);
    for (size_t i = 0; i < capacity; i++) {
        cr_assert(buffy_read(&buffer, &letter, 1) == 0);
    }
}

Test(buffy, empty_write_in_dynamic_buffer)
{
    struct buffy buffer;
    size_t capacity = 10;
    char letter;

    cr_assert_eq(buffy_create(&buffer, capacity, BUFFY_DYNAMIC_SIZE_STRATEGY), 0);
    cr_assert((size_t)buffy_write(&buffer, "", 0) == 0);
    cr_assert(buffer.size == 0);
    for (size_t i = 0; i < capacity; i++) {
        cr_assert(buffy_read(&buffer, &letter, 1) == 0);
    }
}

Test(buffy, multiple_one_write_in_fixed_buffer)
{
    struct buffy buffer;
    size_t capacity = 10;
    const char *data = "Hello, world!";
    size_t size = strlen(data);
    char letter;

    cr_assert_eq(buffy_create(&buffer, capacity, BUFFY_FIXED_SIZE_STRATEGY), 0);
    for (size_t i = 0; i < size; i++) {
        if (i < capacity) {
            cr_assert((size_t)buffy_write(&buffer, &data[i], 1) == 1);
            cr_assert(buffer.size == i + 1);
            cr_assert(buffer.capacity >= i + 1);
        } else {
            cr_assert((size_t)buffy_write(&buffer, &data[i], 1) == 0);
            cr_assert(buffer.size == capacity);
            cr_assert(buffer.capacity >= capacity);
        }
    }
    for (size_t i = 0; i < size; i++) {
        if (i < capacity) {
            cr_assert(buffy_read(&buffer, &letter, 1) == 1);
        } else {
            cr_assert(buffy_read(&buffer, &letter, 1) == 0);
        }
    }
}