const GPIO_BASE: u32 = 0x3F20_0000;
const GPIO_HIGH: u32 = 0x3F20_001C;
const GPIO_LOW: u32 = 0x3F20_0028;
const GPIO_READ: u32 = 0x3F20_0034;

pub fn _gpio_set(pin: u32, output: bool) {
    unsafe {
        // Writing to the GPIO Function Select registers

        if (0..53).contains(&pin) {
            let reg = (GPIO_BASE + 0x4 * (pin / 10)) as *mut u32;
            let shift = (pin % 10) * 3;
            let mut val = core::ptr::read_volatile(reg);
            val &= !(0b111 << shift); // Bits löschen
            if output {
                val |= 0b001 << shift; // Output setzen
            }
            core::ptr::write_volatile(reg, val);
        } else {
            panic!("Invalid GPIO pin number");
        }
    }
}

pub fn _gpio_write(pin: u32, value: bool) {
    unsafe {
        if (0..31).contains(&pin) {
            if value {
                // Set pin high
                core::ptr::write_volatile(GPIO_HIGH as *mut u32, 1 << pin);
            } else {
                // Set pin low
                core::ptr::write_volatile(GPIO_LOW as *mut u32, 1 << pin);
            }
        } else if (32..53).contains(&pin) {
            if value {
                // Set pin high
                core::ptr::write_volatile((GPIO_HIGH + 0x4) as *mut u32, 1 << (pin - 32));
            } else {
                // Set pin low
                core::ptr::write_volatile((GPIO_LOW + 0x4) as *mut u32, 1 << (pin - 32));
            }
        } else {
            panic!("Invalid GPIO pin number");
        }
    }
}

pub fn _gpio_read(pin: u32) -> bool {
    unsafe {
        if (0..53).contains(&pin) {
            let fsel_reg = GPIO_BASE + 0x4 * (pin / 10);
            let fsel_val = core::ptr::read_volatile(fsel_reg as *const u32);
            let fsel_bits = (fsel_val >> ((pin % 10) * 3)) & 0b111;
            if fsel_bits != 0b000 {
                panic!("GPIO is not configured as input");
            }
            return if (0..32).contains(&pin) {
                (core::ptr::read_volatile(GPIO_READ as *const u32) & (1 << pin)) != 0
            } else {
                (core::ptr::read_volatile((GPIO_READ + 0x4) as *const u32) & (1 << (pin - 32))) != 0
            };
        } else {
            panic!("Invalid GPIO pin number");
        }
    }
}
