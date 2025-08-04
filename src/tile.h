#pragma once
#include "Raquet.h"
#include "palette.h"

typedef struct {
    uint8_t pal;
    uint8_t values[64];
    uint32_t* color_data;
    SDL_Texture* texture;
} tile_struct;

extern Raquet_Rect tile_rect;

extern void tile_init(tile_struct* tile);

extern void tile_update_texture(tile_struct* tile);

extern void tile_update_pixel(tile_struct* tile, int pos, int value);

extern void _2bpp_to_tile(uint8_t data[16], tile_struct* tile);

extern void _tile_to_2bpp(tile_struct* tile, uint8_t data[16]);
