#include <stdio.h>
#include <stdint.h>
#include <stddef.h>

struct A {char c; int i; char d; };
struct B {int i; char c; char d; };
struct __attribute__((packed)) C {char c; int i; char d;};

int main(void){
    printf("sizeof(A)=%zu sizeof(B)=%zu sizeof(C)=%zu\n",
            sizeof(struct A), sizeof(struct B), sizeof(struct C));
    printf("A offsets: c=%zu i=%zu d=%zu\n",
            offsetof(struct A, c), offsetof(struct A, i), offsetof(struct A, d));
    printf("B offsets: i=%zu c=%zu d=%zu\n",
            offsetof(struct B, i), offsetof(struct B, c), offsetof(struct B, d));
    printf("C offsets: c=%zu i=%zu d=%zu\n",
            offsetof(struct C, c), offsetof(struct C, i), offsetof(struct C, d));
    return 0;
    
}