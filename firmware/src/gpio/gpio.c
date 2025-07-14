#include "gpio.h"

#define GPFSEL0 ((volatile uint32_t*)(GPIO_BASE + 0x00))
#define GPFSEL1 ((volatile uint32_t*)(GPIO_BASE + 0x04))
#define GPFSEL2 ((volatile uint32_t*)(GPIO_BASE + 0x08))
#define GPSET0  ((volatile uint32_t*)(GPIO_BASE + 0x1C))
#define GPCLR0  ((volatile uint32_t*)(GPIO_BASE + 0x28))
#define GPLEV0  ((volatile uint32_t*)(GPIO_BASE + 0x34))

void gpio_set_mode(uint32_t gpio, gpio_mode_t mode) {
    volatile uint32_t* reg = GPFSEL0 + (gpio / 10);  // je 10 GPIOs pro GPFSEL Register
    uint32_t shift = (gpio % 10) * 3;
    uint32_t val = *reg;
    val &= ~(0x7 << shift);          // Lösche alte Bits
    if (mode == GPIO_OUTPUT) {
        val |= (0x1 << shift);       // Setze Output Modus
    }
    *reg = val;
}

void gpio_write(uint32_t gpio, int value) {
    if (value) {
        *GPSET0 = (1 << gpio);       // Setze Pin
    } else {
        *GPCLR0 = (1 << gpio);       // Lösche Pin
    }
}

int gpio_read(uint32_t gpio) {
    return ((*GPLEV0 & (1 << gpio)) != 0);
}
