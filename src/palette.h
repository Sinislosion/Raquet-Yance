#pragma once
#include "Raquet.h"

extern uint8_t palette[8][4];

extern int palette_current;
extern int palette_current_color;
extern int palette_current_color_id;

/* Sets which palette is in use */
extern void palette_current_set(int i);

/* Sets which palette color is in use */
extern void palette_current_color_set(int i);

extern void palette_current_color_value_set(int i);

extern uint32_t palette_rgb_get(int pal, int col);
