#include <stdio.h>
#include <stdint.h>

#define RB_SIZE 4

typedef struct {
    uint8_t data[RB_SIZE];
    uint32_t head;
    uint32_t tail;
    uint32_t count;
} ring_t;

void rb_init(ring_t *rb){
    rb->head = 0;
    rb->tail = 0;
    rb->count = 0;
}
//return 0 on success, -1 if the buffer is full
int rb_push(ring_t *rb , uint8_t byte){
    if(rb->count == RB_SIZE){
        return -1; // buffer is full
    }
    rb->data[rb->head] = byte;
    rb->head = (rb->head + 1) % RB_SIZE;
    rb->count++;
    return 0; // success
}

//return 0 on success and stores the byte in *byte; -1 if empty
int rb_pop(ring_t *rb, uint8_t *byte){
    if(rb->count == 0){
        return -1; // buffer is empty
    }
    *byte = rb->data[rb->tail];
    rb->tail = (rb->tail + 1) % RB_SIZE;
    rb->count--;
    return 0; // success
}

//return 1 if full, else 0

int rb_is_full(const ring_t *rb){
    return rb->count == RB_SIZE;
}

int main(void){
    ring_t rb;
    uint8_t v;
    rb_init(&rb);

   printf("pop on empty: %d (want -1)\n", rb_pop(&rb, &v));

    for (uint8_t i = 1; i <= 4; i++)
        printf("push %u -> %d (want 0)\n", i, rb_push(&rb, i));
    printf("push 5 -> %d (want -1, full)\n", rb_push(&rb, 5));
    printf("is_full = %d (want 1)\n", rb_is_full(&rb));

    rb_pop(&rb, &v); printf("pop -> %u (want 1)\n", v);
    rb_pop(&rb, &v); printf("pop -> %u (want 2)\n", v);

    rb_push(&rb, 6);   // this write wraps around the end of the array
    rb_push(&rb, 7);
    for (int i = 0; i < 4; i++) {
        rb_pop(&rb, &v);
        printf("pop -> %u\n", v);   // want 3 4 6 7
    }
    printf("pop on empty: %d (want -1)\n", rb_pop(&rb, &v));
    return 0;
}