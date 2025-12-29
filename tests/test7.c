#include <stdio.h>
#include "allocator.h"
#include "types.h"

int main() {
    printf("--- Starting Test 7 - \"Edge Cases\" ---\n");

    void* ptr;

    printf("[1] Allocating 0 bytes...\n");
    ptr = allocate(0);
    if (ptr == NULL)  {
        printf("    FAIL: allocate(0) returned NULL\n");
    } else {
        printf("    PASS: allocate(0) returned non-null pointer\n");
    }
    if (ptr) freemem(ptr);

    printf("[2] Reallocate(NULL, 100)...\n");
    ptr = reallocate(NULL, 100);
    if (ptr == NULL) {
        printf("    FAIL: reallocate(NULL) returned NULL\n");
    } else {
        printf("    PASS: reallocate(NULL) created new allocation\n");
    }

    printf("[3] Reallocate(ptr, 0)...\n");
    void* result = reallocate(ptr, 0);
    if (result == NULL) {
        printf("    PASS: reallocate(ptr, 0) returned NULL (freed)\n");
    } else {
        printf("    WARN: reallocate(ptr, 0) returned pointer %p (check implementation)\n", result);
        freemem(result);
    }

    printf("[4] Callocate huge amount...\n");
    const size_t huge = 1024 * 1024;
    ptr = callocate(huge, huge);    // 1 TiB
    if (ptr == NULL) {
        printf("    PASS: Huge allocation (1 TiB) failed gracefully.\n");
    } else {
        printf("    WARN: Huge allocation (1 TiB) succeeded.\n    Do you have TBs of RAM? If not, this is an error.\n");
        freemem(ptr);
    }

    printf("--- Test 7 Finished ---\n");
    return 0;
}