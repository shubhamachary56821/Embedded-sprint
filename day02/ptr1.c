#include <stdio.h>
#include <stdint.h>

int main(void) {
    int x = 10;
    int *p = &x;

    printf("x = %d\n", x);
    printf("address of x = %p\n", (void *)&x);
    printf("p holds      = %p\n", (void *)p);
    printf("*p           = %d\n", *p);

    *p = 20;
    printf("after *p = 20, x = %d\n", x);

    int arr[3] = {100, 200, 300};
    int *q = arr;
    printf("q[0]=%d  *(q+1)=%d  *(q+2)=%d\n", q[0], *(q + 1), *(q + 2));
    printf("q=%p  q+1=%p\n", (void *)q, (void *)(q + 1));
    return 0;
}