#include <stdio.h>
#include "allocator.h"
#include "types.h"

#define MAX_COUNT 1048576   // 1 MiB

int main() {
    printf("--- Starting Test 2 - \"Large allocations\" ---\n");

    byte* array = callocate(1, sizeof(byte));

    for(int nmemb = 1; nmemb <= MAX_COUNT; nmemb++) {
        byte* new_array = reallocate(array, nmemb * sizeof(byte));

        if (new_array == NULL) {
            fprintf(stderr, "\nWARN: Allocation returned NULL at nmemb = %d\n", nmemb);
            break;
        }

        array = new_array;

        array[nmemb - 1] = 'a';
        
        printf("Current size: %d bytes\r", nmemb);
        fflush(stdout);
    }

    freemem(array);
    printf("Allocated 1 MiB successfully.");
    printf("\n--- Test 2 Finished ---\n");
    return 0;
}