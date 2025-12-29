#include <stddef.h>
#include "allocator.h"

void* malloc(size_t size) {
    return allocate(size);
}

void free(void* ptr) {
    freemem(ptr);
}

void* realloc(void* ptr, size_t size) {
    return reallocate(ptr, size);
}

void* calloc(size_t nmemb, size_t size) {
    return callocate(nmemb, size);
}
