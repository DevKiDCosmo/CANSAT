#![no_std]
#![no_main]

use core::arch::asm;
use core::panic::PanicInfo;

//pub mod framebuffer;
//use display::framebuffer;

pub mod gpio;
use gpio::{_gpio_read, _gpio_set, _gpio_write};

mod boot {
    use core::arch::global_asm;

    global_asm!(".section .text._start");
}

#[unsafe(no_mangle)]
pub extern "C" fn _start() -> ! {
    //if let Some(fb) = framebuffer::Framebuffer::init() {
    //    fb.draw_char(10, 10, 'A', 0xFFFFFF, 0x000000);
    //    fb.draw_char(20, 10, 'B', 0x00FF00, 0x000000);
    //}

    unsafe {
        // Setze PIN29 = GPIO5 als Ausgang, PIN40 = GPIO21 als Asugang
        _gpio_set(29, true);
        _gpio_set(5, true);
        _gpio_set(40, true);
        _gpio_set(21, true);

        _gpio_set(25, true); // Setze GPIO25 als Eingang

        let mut _c: bool = _gpio_read(25); // Lese den Zustand von GPIO25

        loop {
            _gpio_write(29, true);
            _gpio_write(5, true);
            _gpio_write(40, true);
            _gpio_write(21, true);

            for _ in 1..50000 {
                asm!("nop");
            }

            _gpio_write(29, false);
            _gpio_write(5, false);
            _gpio_write(40, false);
            _gpio_write(21, false);

            for _ in 1..50000 {
                asm!("nop");
            }
        }
    }
}

#[panic_handler]
fn panic(_info: &PanicInfo) -> ! {
    loop {}
}
