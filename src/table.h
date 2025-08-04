#pragma once
#include "tile.h"
#include "file.h"

// TODO: A LOT

/* limit because i hate you */
#define table_tiles_max 8192

extern tile_struct table_tiles[table_tiles_max];

extern char* rom_binary;
extern int rom_tile_count;

typedef enum {
    sprite_size_8x8,
    sprite_size_8x16
} table_sprite_size_modes;

extern table_sprite_size_modes table_sprite_size_mode;

extern void table_init();

extern void table_update_palette();

extern void table_load(char* filename);

extern void table_new(int tile_count);

extern void table_save();

extern int table_sprite_size_mode_translate(int t);

extern uint8_t table_pixel_get_value(int x, int y);

extern void table_pixel_set_value(int x, int y, int value);
