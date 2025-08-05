#pragma once

#include "Raquet.h"
#include "table.h"

typedef struct pixel_struct {
	SDL_FRect rect;
	uint16_t size;
	uint8_t * values;
} pixel_struct;

extern pixel_struct pixel_new(void);

extern const char* pixel_state_capture(pixel_struct pxl);

extern void pixel_state_plot(pixel_struct pxl);

extern void pixel_state_read(pixel_struct pxl, char* str);

extern int pixel_state_reconstruct(pixel_struct* pxl, char* str);