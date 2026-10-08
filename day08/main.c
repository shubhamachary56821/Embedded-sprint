#include <stdint.h>
volatile uint32_t counter = 5;        /* .data  */
volatile uint32_t zeroed;             /* .bss   */
int main(void) {
    while (1) { counter++; zeroed = counter; }
}