#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"

static int failures = 0;
#define CHECK(cond) do { \
    if (!(cond)) { \
        fprintf(stderr, "FAIL %s:%d: %s\n", __FILE__, __LINE__, #cond); \
        failures++; \
    } \
} while (0)

static void test_sanity(void) {
    CHECK(1 + 1 == 2);
}

int main(void) {
    test_sanity();

    if (failures == 0) {
        printf("All tests passed\n");
    } else {
        printf("%d checK(s) failed\n", failures);
    }
    return failures != 0;
}