#pragma once

#include "Raquet.h"
#include "8x16font.h"

// TODO: DOCUMENT THESE
#define ascii_char_width    9
#define ascii_char_height   16

extern SDL_Texture * ascii_texture;
extern Raquet_Rect ascii_rect;

extern void ascii_init();

extern void ascii_color_set(uint32_t color_value);

extern void ascii_text_render(unsigned char* text, int x, int y);
