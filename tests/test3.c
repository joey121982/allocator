#include <stdio.h>
#include "allocator.h"
#include "types.h"

#define MAX_COUNT 102400    // 100 KiB

int main() {
    printf("--- Starting Test 3 - \"Aggressive assignments\" ---\n");

    byte* array = callocate(1, sizeof(byte));

    for(int nmemb = 1; nmemb <= MAX_COUNT; nmemb++) {
        byte* new_array = reallocate(array, nmemb * sizeof(byte));

        if (new_array == NULL) {
            fprintf(stderr, "\nWARN: Allocation returned NULL at nmemb = %d\n", nmemb);
            break;
        }

        array = new_array;

        for(int i = 0; i < nmemb; i++) {
            array[i] = 'a';
        }
        array[nmemb - 1] = '\0';
        printf("Current size: %d bytes\r", nmemb);
        fflush(stdout);
    }

    freemem(array);
    printf("Allocated 100 KiB with successful assignments to all bytes.");
    printf("\n--- Test 3 Finished ---\n");
    return 0;
}