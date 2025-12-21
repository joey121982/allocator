#ifndef _ALLOCATOR_H_
#define _ALLOCATOR_H_ 1

#include "types.h"
#include "memblock.h"

void init_allocator();
memb* extend_list(size_t size);
void* allocate(size_t size);
void* callocate(size_t n, size_t size);
void freemem(void* p);
void reallocate(void* p, size_t size);

#endif /* allocator.h */
