#define PERIPHERAL_BASE 0x3F000000
#define GPIO_BASE       (PERIPHERAL_BASE + 0x200000)

#define GPFSEL1    ((volatile unsigned int*)(GPIO_BASE + 0x04))
#define GPSET0     ((volatile unsigned int*)(GPIO_BASE + 0x1C))
#define GPCLR0     ((volatile unsigned int*)(GPIO_BASE + 0x28))

void delay(unsigned int count) {
    while (count--) {
        __asm__("nop");
    }
}

void kernel_main(void) {
    // GPIO16 als Output konfigurieren (Bit 18–20 in GPFSEL1)
    *GPFSEL1 &= ~(0b111 << 18);
    *GPFSEL1 |=  (0b001 << 18);  // Funktion 001 = Output

    while (1) {
        *GPSET0 = (1 << 16);  // LED an
        delay(500000);
        *GPCLR0 = (1 << 16);  // LED aus
        delay(500000);
    }
}
