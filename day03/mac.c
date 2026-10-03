#include <stdio.h>
#include <stdint.h>

#define SQUARE_BAD(x)   x * x
#define SQUARE_OK(x)    ((x) * (x))
#define MAX_BAD(a, b)   (a > b ? a : b)
#define MAX_OK(a, b)    ((a) > (b) ? (a) : (b))

static inline int square_fn(int x) { return x * x; }

int main(void) {
    int n = 3;
    printf("SQUARE_BAD(n+1) = %d\n", SQUARE_BAD(n + 1));
    printf("SQUARE_OK(n+1)  = %d\n", SQUARE_OK(n + 1));
    printf("square_fn(n+1)  = %d\n", square_fn(n + 1));

    int i = 5, j = 5;
    int r = MAX_OK(i++, j);
    printf("MAX_OK(i++, j) = %d, i is now %d\n", r, i);
    return 0;
}