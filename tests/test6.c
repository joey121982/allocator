#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "allocator.h"
#include "types.h"

#define NUM_OPS 10000
#define MAX_PTRS 100
#define MAX_ALLOC_SIZE 5000

typedef struct {
    void* ptr;
    size_t size;
} AllocRecord;

AllocRecord history[MAX_PTRS];

int main() {
    srand(42);      // fixed seed so we can reproduce
    printf("--- Starting Test 6 - \"Randomized Stress Test\" ---\n");

    for (int i = 0; i < MAX_PTRS; i++) {
        history[i].ptr = NULL;
        history[i].size = 0;
    }

    for (int i = 0; i < NUM_OPS; i++) {
        int index = rand() % MAX_PTRS;
        int op = rand() % 3;

        if (history[index].ptr == NULL) {
            size_t size = (rand() % MAX_ALLOC_SIZE) + 1;
            history[index].ptr = allocate(size);
            history[index].size = size;
            if (i % 1000 == 0) printf("Op %d: Allocated %lu bytes at index %d\n", i, size, index);
        } else {
            if (op == 1) {
                freemem(history[index].ptr);
                history[index].ptr = NULL;
                history[index].size = 0;
                if (i % 1000 == 0) printf("Op %d: Freed index %d\n", i, index);
            } else if (op == 2) {
                size_t new_size = (rand() % MAX_ALLOC_SIZE) + 1;
                void* ret = reallocate(history[index].ptr, new_size);
                if (ret != NULL) {
                    history[index].ptr = ret;
                    history[index].size = new_size;
                }
                if (i % 1000 == 0) printf("Op %d: Reallocated index %d to %lu bytes\n", i, index, new_size);
            }
        }
    }

    printf("Cleaning up...\n");
    for (int i = 0; i < MAX_PTRS; i++) {
        if (history[i].ptr != NULL) {
            freemem(history[i].ptr);
        }
    }

    printf("--- Test 6 Finished ---\n");
    return 0;
}