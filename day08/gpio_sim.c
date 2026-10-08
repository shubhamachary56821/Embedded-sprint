#include <stdio.h>
#include <stdint.h>

typedef struct {
    volatile uint32_t MODER;    /* 0x00 */
    volatile uint32_t OTYPER;   /* 0x04 */
    volatile uint32_t OSPEEDR;  /* 0x08 */
    volatile uint32_t PUPDR;    /* 0x0C */
    volatile uint32_t IDR;      /* 0x10 */
    volatile uint32_t ODR;      /* 0x14 */
    volatile uint32_t BSRR;     /* 0x18 */
} GPIO_t;

/* On real hardware: #define GPIOA ((GPIO_t *)0x40020000)
   Here we fake it with ordinary memory. */
static GPIO_t fake_gpio;
#define GPIOA (&fake_gpio)

/* Emulates what the hardware does when BSRR is written. */
static void hw_apply_bsrr(GPIO_t *g) {
    uint32_t v = g->BSRR;
    g->ODR |=  (v & 0xFFFFu);          /* low 16 bits: set */
    g->ODR &= ~(v >> 16);              /* high 16 bits: reset */
    g->BSRR = 0;
}

#define LED_PIN 5

static void led_init(void) {
    GPIOA->MODER &= ~(3u << (LED_PIN * 2));   /* clear the 2-bit mode field */
    GPIOA->MODER |=  (1u << (LED_PIN * 2));   /* 01 = general-purpose output */
}
static void led_on(void)     { GPIOA->ODR |=  (1u << LED_PIN); }   /* read-modify-write */
static void led_off(void)    { GPIOA->ODR &= ~(1u << LED_PIN); }
static void led_toggle(void) { GPIOA->ODR ^=  (1u << LED_PIN); }
static void led_on_atomic(void)  { GPIOA->BSRR = (1u << LED_PIN);        hw_apply_bsrr(GPIOA); }
static void led_off_atomic(void) { GPIOA->BSRR = (1u << (LED_PIN + 16)); hw_apply_bsrr(GPIOA); }

static void show(const char *label) {
    printf("%-14s MODER=0x%08X  ODR=0x%08X  LED=%s\n", label,
           GPIOA->MODER, GPIOA->ODR, (GPIOA->ODR >> LED_PIN) & 1 ? "ON" : "off");
}

int main(void) {
    printf("sizeof(GPIO_t) = %zu bytes\n", sizeof(GPIO_t));
    led_init();         show("after init");
    led_on();           show("led_on");
    led_off();          show("led_off");
    led_toggle();       show("led_toggle");
    led_toggle();       show("led_toggle");
    led_on_atomic();    show("on (BSRR)");
    led_off_atomic();   show("off (BSRR)");
    return 0;
}