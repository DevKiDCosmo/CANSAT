#include "framebuffer.h"
#include "mailbox.h"
#include "font8x8_basic.h"

uint32_t mailbox[36] __attribute__((aligned(16)));
uint32_t *framebuffer;
int fb_width, fb_height, fb_pitch;

int framebuffer_init(int width, int height, int depth) {
    mailbox[0] = 35 * 4;
    mailbox[1] = 0;
    mailbox[2] = 0x00048003; mailbox[3] = 8; mailbox[4] = 8;
    mailbox[5] = width; mailbox[6] = height;
    mailbox[7] = 0x00048004; mailbox[8] = 8; mailbox[9] = 8;
    mailbox[10] = width; mailbox[11] = height;
    mailbox[12] = 0x00048005; mailbox[13] = 4; mailbox[14] = 4;
    mailbox[15] = depth;
    mailbox[16] = 0x00040001; mailbox[17] = 8; mailbox[18] = 8;
    mailbox[19] = 0; mailbox[20] = 0;
    mailbox[21] = 0x00040008; mailbox[22] = 4; mailbox[23] = 4;
    mailbox[24] = 0;
    mailbox[25] = 0x00040009; mailbox[26] = 4; mailbox[27] = 4;
    mailbox[28] = 0;
    mailbox[29] = 0x0004800B; mailbox[30] = 4; mailbox[31] = 4;
    mailbox[32] = 0;
    mailbox[33] = 0;
    mailbox[34] = 0;

    if (mailbox_call(MAILBOX_FRAMEBUFFER, mailbox)) {
        framebuffer = (uint32_t *)((uint64_t)mailbox[19]);
        fb_pitch = mailbox[28];
        fb_width = mailbox[5];
        fb_height = mailbox[6];
        return 1;
    }
    return 0;
}

void framebuffer_put_pixel(int x, int y, uint32_t color) {
    framebuffer[y * (fb_pitch / 4) + x] = color;
}

void framebuffer_clear(uint32_t color) {
    for (int y = 0; y < fb_height; y++)
        for (int x = 0; x < fb_width; x++)
            framebuffer_put_pixel(x, y, color);
}

void framebuffer_draw_char(char c, int x, int y, uint32_t color) {
    uint8_t *glyph = (uint8_t *)font8x8_basic[(int)c];
    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            if (glyph[row] & (1 << col)) {
                framebuffer_put_pixel(x + col, y + row, color);
            }
        }
    }
}
