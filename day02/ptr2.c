#include <stdio.h>
#include <stdint.h>

int main(void) {
    uint32_t arr[4] = {1, 2, 3, 4};
    uint32_t *p = arr;

    printf("sizeof(arr) = %zu\n", sizeof(arr));
    printf("sizeof(p)   = %zu\n", sizeof(p));

    uint8_t  *b = (uint8_t *)arr;
    uint16_t *h = (uint16_t *)arr;
    printf("p+1 - p     = %ld element, %ld bytes apart\n",
           (long)((p + 1) - p), (long)((char *)(p + 1) - (char *)p));
    printf("b+1 is %ld byte(s) after b\n", (long)((char *)(b + 1) - (char *)b));
    printf("h+1 is %ld byte(s) after h\n", (long)((char *)(h + 1) - (char *)h));

    int a = 5, c = 9;
    const int *r1 = &a;     // pointer to const int
    int *const r2 = &a;     // const pointer to int

    r1 = &c;                // allowed?
    // *r1 = 7;             // allowed? try uncommenting
    *r2 = 7;                // allowed?
    // r2 = &c;             // allowed? try uncommenting

    printf("a=%d c=%d *r1=%d *r2=%d\n", a, c, *r1, *r2);
    return 0;
}