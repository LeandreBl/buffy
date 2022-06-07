#ifndef BUFFY_H_
#define BUFFY_H_

#include <stdint.h>
#include <stddef.h>
#include <unistd.h>

/**
 * \enum buffy_allocation_strategy
 * 
 * \brief The different allocation strategies for the buffy.
 * 
 * \var BUFFY_FIXED_SIZE_STRATEGY: The buffy will allocate a fixed size of memory and can't be reallocated.
 * \var BUFFY_DYNAMIC_SIZE_STRATEGY: The buffy will reallocate itself on different operations.
 */
enum buffy_allocation_strategy {
    BUFFY_FIXED_SIZE_STRATEGY = 1,
    BUFFY_DYNAMIC_SIZE_STRATEGY = 2
};

/**
 * \struct buffy
 * \brief The buffy structure.
 * 
 * The buffy structure is used to store a buffer of bytes
 * and to provide a simple interface to manipulate it.
 * 
 * \var data: The buffer of bytes.
 * \var size: The number of bytes used by the buffer.
 * \var capacity: The capacity of the buffer.
 * \var flags: The allocation strategy of the buffer.
 */
struct buffy {
    uint8_t *data;
    size_t size;
    size_t capacity;
    enum buffy_allocation_strategy flags;
};

/**
 * \fn int buffy_create(struct buffy *buffy, size_t capacity)
 * \brief Function to initialize a buffy.
 *
 * \param buffy The buffy to initialize.
 * \param capacity The initial capacity of the buffy.
 * \param flags The allocation strategy of the buffy.
 * 
 * \note The capacity of the buffy is doubled every time it is full (with BUFFY_DYNAMIC_SIZE_STRATEGY flag)
 * \note The capacity of the buffy is set to the given capacity and will no longer change (with BUFFY_FIXED_SIZE_STRATEGY flag)
 * 
 * \return 0 on success, -1 on failure, errno is set accordingly.
 */

int buffy_create(struct buffy *buffy, size_t capacity, enum buffy_allocation_strategy flags) __nonnull((1));

/**
 * \fn int buffy_destroy(struct buffy *buffy)
 * \brief Function to destroy a buffy.
 *
 * \param buffy The buffy to destroy.
 */
void buffy_destroy(struct buffy *buffy) __nonnull((1));

/**
 * \fn int buffy_clear(struct buffy *buffy)
 * \brief Function to clear the content of a buffy.
 *
 * \param buffy The buffy to clear.
 */
void buffy_clear(struct buffy *buffy) __nonnull((1));

/**
 * \fn ssize_t buffer_write(struct buffy *buffy, const void *data, size_t size)
 * \brief Function to write data to a buffy, similar to the write() system call.
 * 
 * \note The data is appended to the buffy.
 * \note The buffy is automatically resized if it is full.
 * 
 * \param buffy The buffy to write to.
 * \param data The pointer to the data to write.
 * \param size The size of the data to write (in bytes).
 * 
 * \return The number of bytes written on success, -1 on failure, errno is set accordingly.
 */
ssize_t buffy_write(struct buffy *buffy, const void *data, size_t size) __nonnull((1, 2));

/**
 * \fn ssize_t buffy_read(struct buffy *buffy, void *data, size_t size)
 * \brief Function to read data from a buffy, similar to the read() system call.
 * 
 * \note The data is read from the buffy.
 * 
 * \param buffy The buffy to read from.
 * \param data The pointer to the data to read.
 * \param size The size of the data to read (in bytes).
 * 
 * \return The number of bytes read on success, -1 on failure, errno is set accordingly.
 */
ssize_t buffy_read(struct buffy *buffy, void *data, size_t size) __nonnull((1, 2));

/**
 * \fn ssize_t buffer_peek(struct buffy *buffy, void *data, size_t size)
 * \brief Function to peek data from a buffy, similar to the buffy_read() function, but does not remove the data from the buffy.
 * 
 * \param buffy The buffy to read from.
 * \param data The pointer to the data to read.
 * \param size The size of the data to read (in bytes).
 * 
 * \return The number of bytes peeked on success, -1 on failure, errno is set accordingly.
 */
ssize_t buffy_peek(struct buffy *buffy, void *data, size_t size) __nonnull((1, 2));

/**
 * \fn ssize_t buffy_find(struct buffy *buffy, const void *data, size_t size)
 * \brief Function to find data in a buffy, returns the offset of the first occurrence of the data in the buffy.
 * 
 * \param buffy The buffy to search in.
 * \param data The pointer to the data to search for.
 * \param size The size of the data to search for (in bytes).
 * 
 * \return The offset of the first occurrence of the data in the buffy on success, -1 on failure.
 */
ssize_t buffy_find(struct buffy *buffy, const void *data, size_t size) __nonnull((1, 2));


/**
 * \fn int buffy_resize_capacity(struct buffy *buffy, size_t size)
 * \brief Function to resize a buffy.
 * 
 * \param buffy The buffy to resize.
 * \param size The new size of the buffy.
 * 
 * \note This function will fail if the buffy is not BUFFY_DYNAMIC_SIZE_STRATEGY.
 * 
 * \return 0 on success, -1 on failure, errno is set accordingly.
 */
int buffy_resize_capacity(struct buffy *buffy, size_t size) __nonnull((1));

#endif /* !BUFFY_H_ */