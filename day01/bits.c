#include <stdio.h>
#include <stdint.h>

void print_bits(uint8_t v){
    for (int i = 7; i >= 0; i--)
        printf("%d", (v >> i) & 1);
    printf("\n");
}

int main(void){
    uint8_t reg = 0x00;

    reg |= (1 << 5); printf("set 5:    "); print_bits(reg);
    reg |= (1 << 2); printf("set 2:    "); print_bits(reg);
    reg ^= (1 << 5); printf("toogle 5: "); print_bits(reg);
    reg &= ~(1 << 2); printf("clear 2: "); print_bits(reg);

    reg = 0b10100110;
    printf("bit 1 is %d, bit 2 is %d\n", (reg >> 1) & 1, (reg >> 3) & 1);
    return 0;
}