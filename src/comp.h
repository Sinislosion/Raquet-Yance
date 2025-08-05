#pragma once
#include "Raquet.h"
#include "bmp.h"

extern Raquet_Rect comp_space;

// TODO: Finish all functions

typedef enum comp_targets {
    rom_table,
    editor,
    manual
} comp_targets;

/* Current composition target */
extern comp_targets comp_target;

/* Sprite table cursor and selection */
extern Raquet_Point table_cursor;
extern Raquet_Rect table_selection;
extern Raquet_Point table_selection_origin;

extern Raquet_Point editor_cursor;
extern Raquet_Rect editor_selection;
extern Raquet_Point editor_selection_origin;

extern int pos_addr; // TODO: figure out wtf pos_addr means

extern void comp_init();
extern void comp_render();
extern void comp_update();
