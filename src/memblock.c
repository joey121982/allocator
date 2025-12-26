#include "memblock.h"
#include "types.h"

void split_block(memb* block, size_t size) {
    size_t block_size = block->header.size;
    size_t remainder = block_size - size;

    if(remainder < sizeof(memb)) {
        block->header.size = block_size | 1;
        return;
    }

    memb* old_next = block->next;

    block->header.size = size | 1;
    block->next = (memb*)((byte*)block + size);
    
    memb* new_block = block->next;
    new_block->header.size = block_size & ~1L;
    new_block->prev = block;
    new_block->next = old_next;

    if(old_next != NULL) {
        old_next->prev = new_block;
    }
}

memb* coalesce_blocks(memb* block) {
    memb* next_block = block->next;
    memb* prev_block = block->prev;

    size_t size = block->header.size & ~1L;

    if(next_block != NULL && (next_block->header.size & 1) == 0) {
        size_t next_size = next_block->header.size;

        if((byte*)block + size == (byte*)next_block) {
            size_t total_size = size + (next_size & ~1L);
            block->header.size = total_size;
            block->next = next_block->next;
            if(block->next != NULL) block->next->prev = block;
        }
    }

    size = block->header.size & ~1L;

    if(prev_block != NULL && (prev_block->header.size & 1) == 0) {
        size_t prev_size = prev_block->header.size;

        if((byte*)prev_block + prev_size == (byte*)block) {
            size_t total_size = size + (prev_size & ~1L);
            prev_block->header.size = total_size;
            prev_block->next = block->next;
            if(prev_block->next != NULL) prev_block->next->prev = prev_block;

            block = prev_block;
        }
    }

    return block;
}