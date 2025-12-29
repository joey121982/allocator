/* wrapper.c */
#include <stddef.h>
#include "allocator.h" // Ensures we see your function declarations

// Standard malloc signature
void* malloc(size_t size) {
    return allocate(size);
}

// Standard free signature
void free(void* ptr) {
    freemem(ptr);
}

// Standard realloc signature
void* realloc(void* ptr, size_t size) {
    return reallocate(ptr, size);
}

// Standard calloc signature
void* calloc(size_t nmemb, size_t size) {
    return callocate(nmemb, size);
}