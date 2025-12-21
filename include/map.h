#ifndef _MAP_H_
#define _MAP_H_ 1

#include "types.h"

void* get_mem_slab(size_t size);
void free_mem_slab(void* ptr, size_t size);

#endif /* map.h */