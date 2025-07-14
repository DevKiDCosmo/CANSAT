#include "mailbox.h"

uint32_t mailbox_call(uint8_t channel, uint32_t *mailbox_msg) {
    uint32_t addr = ((uint32_t)(uint64_t)mailbox_msg) & ~0xF;
    uint32_t value = addr | (channel & 0xF);

    while (*MAILBOX_STATUS & MAILBOX_FULL);
    *MAILBOX_WRITE = value;

    while (1) {
        while (*MAILBOX_STATUS & MAILBOX_EMPTY);
        if (*MAILBOX_READ == value)
            return mailbox_msg[1] == 0x80000000; // OK
    }
}
