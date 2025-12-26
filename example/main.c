#include <stdio.h>
#include <stdlib.h> // for exit
#include "allocator.h"

#define N 1000000

void check_ptr(void* ptr, const char* msg) {
    if (ptr == NULL) {
        printf("ERROR: %s returned NULL!\n", msg);
        exit(1);
    }
}

int main() {
    printf("--- Starting Test ---\n");

    /* TEST ALLOCATE */
    printf("[1] Allocating %lu bytes...\n", N * sizeof(int));
    int* x = (int*)allocate(N * sizeof(int));
    check_ptr(x, "allocate");

    printf("[1] Filling data...\n");
    for(int i = 0; i < N; i++) {
        x[i] = 2 * (i + 1);
    }

    long sum = 0;
    for(int i = 0; i < N; i++) {
        sum += x[i];
    }
    printf("[1] Sum: %ld\n", sum);

    /* TEST REALLOCATE */
    printf("\n[2] Reallocating to %lu bytes...\n", N * 2 * sizeof(int));
    
    // STORE NEW POINTER
    int* new_x = (int*)reallocate(x, N * 2 * sizeof(int));
    check_ptr(new_x, "reallocate");
    x = new_x; // Update x only if successful

    printf("[2] Filling new data...\n");
    for(int i = 0; i < N * 2; i++) {
        x[i] = 2 * (i + 1);
    }

    sum = 0;
    for(int i = 0; i < N * 2; i++) {
        sum += x[i];
    }
    printf("[2] Sum, after doubling size: %ld\n", sum);

    /* TEST FREE */
    printf("\n[3] Freeing memory...\n");
    freemem(x);
    printf("[3] Freed successfully.\n");

    /* TEST CALLOCATE */
    printf("\n[4] Callocating...\n");
    x = (int*)callocate(10, sizeof(int));
    check_ptr(x, "callocate");

    printf("Empty vector: ");
    for(int i = 0; i < 10; i++) {
        printf("%d ", x[i]);
    }
    printf("\n");

    freemem(x);
    printf("--- Test Finished ---\n");

    return 0;
}