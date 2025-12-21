#ifndef _ALLOCATOR_H_
#define _ALLOCATOR_H_ 1

#include "types.h"

void* allocate(size_t size);
void* callocate(size_t n, size_t size);
void freemem(void* _Nullable p);
void reallocate(void* _Nullable p, size_t size);

#endif /* allocator.h */
