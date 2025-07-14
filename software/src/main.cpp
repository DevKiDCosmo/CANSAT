#include <bcm2835.h>


int main() {
    if (!bcm2835_init()) {
        return 1;
    }

    bcm2835_gpio_fsel(RPI_GPIO_P1_12, BCM2835_GPIO_FSEL_OUTP);

    while (1) {
        bcm2835_gpio_write(RPI_GPIO_P1_12, HIGH);
        bcm2835_delay(500);
        bcm2835_gpio_write(RPI_GPIO_P1_12, LOW);
        bcm2835_delay(500);
    }

    bcm2835_close();
    return 0;
}