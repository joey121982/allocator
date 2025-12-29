#include <stdio.h>
#include <stdlib.h>
#include "allocator.h"
#include "types.h"

#define ORIGINAL_SIZE 1000
#define SHRUNK_SIZE 500

int main() {
    printf("--- Starting Test 5 - \"Realloc Shrinking\" ---\n");

    printf("[1] Allocating array of size %d...\n", ORIGINAL_SIZE);
    int* array = (int*)allocate(ORIGINAL_SIZE * sizeof(int));
    if (!array) return 1;

    for(int i = 0; i < ORIGINAL_SIZE; i++) {
        array[i] = i;
    }

    printf("[2] Shrinking array to size %d...\n", SHRUNK_SIZE);
    int* shrunk_array = (int*)reallocate(array, SHRUNK_SIZE * sizeof(int));
    
    if (shrunk_array == NULL) {
        printf("Error: Reallocate returned NULL on shrink.\n");
        return 1;
    }
    array = shrunk_array;

    printf("[3] Verifying data up to index %d...\n", SHRUNK_SIZE - 1);
    int valid = 1;
    for(int i = 0; i < SHRUNK_SIZE; i++) {
        if (array[i] != i) {
            printf("Data corruption at index %d. Expected %d, got %d\n", i, i, array[i]);
            valid = 0;
            break;
        }
    }

    if (valid) printf("Data preserved successfully.\n");

    printf("[4] Growing back to original size...\n");
    array = (int*)reallocate(array, ORIGINAL_SIZE * sizeof(int));
    
    freemem(array);
    printf("--- Test 5 Finished ---\n");
    return 0;
}