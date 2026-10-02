#include <stdio.h>
#include <stdint.h>

int main(void) {
    printf("char=%zu short=%zu int=%zu long=%zu\n",
           sizeof(char), sizeof(short), sizeof(int), sizeof(long));
    printf("uint8_t=%zu uint16_t=%zu uint32_t=%zu uint64_t=%zu\n",
           sizeof(uint8_t), sizeof(uint16_t), sizeof(uint32_t), sizeof(uint64_t));

    uint8_t a = 250;
    a = a + 10;
    printf("uint8_t 250 + 10 = %u\n", a);

    int8_t b = 127;
    b = b + 1;
    printf("int8_t 127 + 1 = %d\n", b);

    uint8_t c = 0;
    c = c - 1;
    printf("uint8_t 0 - 1 = %u\n", c);

    return 0;
}