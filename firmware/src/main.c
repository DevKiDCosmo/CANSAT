#include "./gpio/gpio.h"

#define PERIPHERAL_BASE 0x3F000000
//#define GPIO_BASE       (PERIPHERAL_BASE + 0x200000)

#define GPFSEL1    ((volatile unsigned int*)(GPIO_BASE + 0x04))
#define GPSET0     ((volatile unsigned int*)(GPIO_BASE + 0x1C))
#define GPCLR0     ((volatile unsigned int*)(GPIO_BASE + 0x28))

void delay(unsigned int count) {
    while (count--) {
        __asm__("nop");
    }
}

void kernel_main(void) {
    gpio_set_mode(16, GPIO_OUTPUT);

    while (1) {
        gpio_write(16, 1);  // LED an
        delay(500000); // Sind ca. 0.5 Sekunden - Kann auf 1 ns genau eingestellt werden
        gpio_write(16, 0);  // LED aus
        delay(500000);
    }
}
