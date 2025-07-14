#ifndef GPIO_H
#define GPIO_H

#include <stdint.h>

#define GPIO_BASE 0xFE200000UL  // Basisadresse GPIO (für Pi 4 und Pi Zero 2 W, beachten!)

typedef enum {
    GPIO_INPUT = 0,
    GPIO_OUTPUT = 1,
} gpio_mode_t;

void gpio_set_mode(uint32_t gpio, gpio_mode_t mode);
void gpio_write(uint32_t gpio, int value);
int gpio_read(uint32_t gpio);

#endif
