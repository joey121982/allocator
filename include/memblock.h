#ifndef _MEMBLOCK_H_
#define _MEMBLOCK_H_ 1

#include "types.h"

#define PAGE_SIZE 4096
#define ALIGN_TO_PAGE(x) ((x + PAGE_SIZE - 1) & ~(PAGE_SIZE - 1))

#define PAYLOAD_SIZE 16
#define ALIGN_PAYLOAD(x) ((x + PAYLOAD_SIZE - 1) & ~(PAYLOAD_SIZE - 1))

#define BLOCK_SIZE (sizeof(memb))

typedef struct {
    size_t size;
} memb_header;

typedef struct memory_block {
    memb_header header;
    struct memory_block* next;
    struct memory_block* prev;
} memb;

void split_block(memb* block, size_t size);
memb* coalesce_blocks(memb* block);

#endif /* memblock.h */
