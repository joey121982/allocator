#ifndef _MEMBLOCK_H_
#define _MEMBLOCK_H_ 1

#include "types.h"

typedef struct {
    size_t size;
} memb_header;

typedef struct memory_block {
    memb_header header;
    struct memory_block* next;
    struct memory_block* prev;
} memb;

#endif /* memblock.h */
