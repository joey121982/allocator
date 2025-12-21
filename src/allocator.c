#include "allocator.h"
#include "map.h"
#include "memblock.h"

static memb* free_list_head;

void init_allocator() {
    free_list_head = NULL;
}

memb* find_free_block(size_t size) {
    memb* addr = free_list_head;

    while (addr != NULL) {
        if (addr->header.size >= size && (addr->header.size & 0x1) != 0x1)
            return addr;
        addr = addr->next;
    }

    return NULL;
}

memb* extend_list(size_t size) {
    void* slab = get_mem_slab(size);

    if (slab == NULL)
        return NULL;            // out of memory

    memb* block = (memb*)slab;
    block->header.size = size;
    block->next = free_list_head;
    block->prev = NULL;

    if(free_list_head != NULL)
        free_list_head->prev = block;

    free_list_head = block;
    return block;
}

void* allocate(size_t size) {
    size_t real_size = ALIGN_PAYLOAD(size + sizeof(memb_header));

    memb* block = find_free_block(real_size);
    if (block == NULL) {
        block = extend_list(real_size);

        if (block == NULL) 
            return NULL;        // out of memory

        split_block(block, real_size);
    }

    return block + sizeof(memb_header);
}