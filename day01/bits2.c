#include <stdio.h>
#include <stdint.h>

int count_set_bits(uint32_t n){
    //return how many bits are 1. 0b10110 ->3
    int count = 0;
    while(n){
        count += n & 1;
        n >>= 1;
    }
    return count;

    int is_power_of_two(uint32_t n){
        //return 1 if n is 1,2,4,8,16,.... or else 0. 0 is NOT a power of two
        if(n == 0) return 0;
        return (n & (n - 1) == 0);
    }

   int main(void) {
    printf("%d (want 3)\n", count_set_bits(0b10110));
    printf("%d (want 0)\n", count_set_bits(0));
    printf("%d (want 32)\n", count_set_bits(0xFFFFFFFF));
    printf("%d %d %d %d (want 1 1 0 0)\n",
           is_power_of_two(64), is_power_of_two(1),
           is_power_of_two(12), is_power_of_two(0));
    return 0;
}
}