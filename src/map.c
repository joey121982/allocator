#include <sys/mman.h>

#include "map.h"

#define ALIGN_TO_PAGE(x) ((x >> 12) + 1) << 12

/**
 * @brief Get memory slab from OS.
 * 
 * @param size number of bytes to request
 */
void* get_mem_slab(size_t size) {
    size_t real_size = ALIGN_TO_PAGE(size);
    int prot = PROT_READ | PROT_WRITE;
    int flags = MAP_PRIVATE | MAP_ANONYMOUS;
    int fd = -1;
    off_t offset = 0;

    void* ptr = mmap(NULL, real_size, prot, flags, fd, offset);
    if (ptr == MAP_FAILED) return NULL;
    return ptr;
}

/**
 * @brief Wrapper for munmap()
 * 
 * @param ptr pointer to slab of memory 
 * @param size slab size in bytes
 */
void free_mem_slab(void* ptr, size_t size) {
    munmap(ptr, size);
}