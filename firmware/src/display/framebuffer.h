#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include <stdint.h>

extern uint32_t *framebuffer;
extern int fb_width;
extern int fb_height;
extern int fb_pitch;

int framebuffer_init(int width, int height, int depth);
void framebuffer_put_pixel(int x, int y, uint32_t color);
void framebuffer_clear(uint32_t color);
void framebuffer_draw_char(char c, int x, int y, uint32_t color);

#endif
