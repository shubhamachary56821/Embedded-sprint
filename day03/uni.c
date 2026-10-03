#include <stdio.h>
#include <stdint.h>

union Reg {
    uint32_t word;
    uint8_t  byte[4];
};

int main(void) {
    union Reg r;
    r.word = 0x11223344;

    printf("sizeof(union Reg) = %zu\n", sizeof(union Reg));
    printf("word    = 0x%08X\n", r.word);
    printf("byte[0] = 0x%02X\n", r.byte[0]);
    printf("byte[1] = 0x%02X\n", r.byte[1]);
    printf("byte[2] = 0x%02X\n", r.byte[2]);
    printf("byte[3] = 0x%02X\n", r.byte[3]);

    if (r.byte[0] == 0x44)
        printf("this machine is little-endian\n");
    else
        printf("this machine is big-endian\n");
    return 0;
}