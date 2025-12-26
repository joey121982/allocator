#include "allocator.h"
#include "map.h"
#include "memblock.h"

#include <string.h>

static memb* free_list_head;

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
    size_t slab_size = ALIGN_TO_PAGE(size);
    void* slab = get_mem_slab(slab_size);

    if (slab == NULL)
        return NULL;            // out of memory

    memb* block = (memb*)slab;
    block->header.size = slab_size;
    block->next = free_list_head;
    block->prev = NULL;

    if(free_list_head != NULL)
        free_list_head->prev = block;

    free_list_head = block;
    return block;
}

void* allocate(size_t size) {
    size_t real_size = ALIGN_PAYLOAD(size + sizeof(memb_header));

    if (real_size < sizeof(memb)) {
        real_size = ALIGN_PAYLOAD(sizeof(memb));
    }

    memb* block = find_free_block(real_size);
    if (block == NULL) {
        block = extend_list(real_size);

        if (block == NULL) 
            return NULL;        // out of memory

    }
    split_block(block, real_size);
    
    return (byte*)block + sizeof(memb_header);
}

void* callocate(size_t n, size_t size) {
    size_t total_size = size * n;

    void* ptr = allocate(total_size);
    if(ptr == NULL)
        return NULL;

    memset(ptr, 0, total_size);
    return ptr;
}

void* reallocate(void* p, size_t size) {
    if(p == NULL)
        return allocate(size);

    if(size == 0) {
        freemem(p);
        return NULL;
    }

    memb_header* header = (memb_header*)((byte*)p - sizeof(memb_header));
    size_t old_size = header->size & ~1L;
    size_t payload_size = old_size - sizeof(memb_header);

    if(size <= payload_size) return p;

    void* new_p = allocate(size);
    if(new_p == NULL)
        return NULL;

    memcpy(new_p, p, payload_size);
    freemem(p);

    return new_p;
}

void freemem(void* p) {
    if(p == NULL) return;

    memb* block = (memb*)((byte*)p - sizeof(memb_header));
    block->header.size &= ~1L;

    block = coalesce_blocks(block);
    
    if(block->header.size >= PAGE_SIZE && (block->header.size % PAGE_SIZE) == 0) {
        if(block->prev) block->prev->next = block->next;
        if(block->next) block->next->prev = block->prev;

        if(block == free_list_head) {
            free_list_head = block->next;
        }

        free_mem_slab(block, block->header.size);
    }
}