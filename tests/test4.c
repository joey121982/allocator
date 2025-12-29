#include <stdio.h>
#include <stdlib.h>
#include "allocator.h"
#include "types.h"

#define BLOCK_COUNT 100
#define BLOCK_SIZE 1024 // 1KB

int main() {
    printf("--- Starting Test 4 - \"Fragmentation / Reuse\" ---\n");

    int* pointers[BLOCK_COUNT];

    printf("[1] Allocating %d blocks of %d bytes...\n", BLOCK_COUNT, BLOCK_SIZE);
    for (int i = 0; i < BLOCK_COUNT; i++) {
        pointers[i] = (int*)allocate(BLOCK_SIZE);
        if (pointers[i] == NULL) {
            fprintf(stderr, "Failed to allocate block %d\n", i);
            exit(1);
        }
        *pointers[i] = i;
    }

    printf("[2] Freeing even-numbered blocks to create holes...\n");
    for (int i = 0; i < BLOCK_COUNT; i += 2) {
        freemem(pointers[i]);
        pointers[i] = NULL;
    }

    printf("[3] Allocating new blocks into the holes...\n");
    for (int i = 0; i < BLOCK_COUNT; i += 2) {
        pointers[i] = (int*)allocate(BLOCK_SIZE);
        if (pointers[i] == NULL) {
            fprintf(stderr, "Failed to reuse memory for block %d\n", i);
            exit(1);
        }
        *pointers[i] = i + 1000;
    }

    printf("[4] Verifying data integrity...\n");
    int errors = 0;
    for (int i = 0; i < BLOCK_COUNT; i++) {
        int expected = (i % 2 == 0) ? (i + 1000) : i;
        if (*pointers[i] != expected) {
            printf("Error at index %d: Expected %d, got %d\n", i, expected, *pointers[i]);
            errors++;
        }
        freemem(pointers[i]);
    }

    if (errors == 0) {
        printf("Integrity check passed.\n");
    } else {
        printf("Integrity check failed with %d errors.\n", errors);
    }

    printf("--- Test 4 Finished ---\n");
    return 0;
}