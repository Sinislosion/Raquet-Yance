#pragma once
#include "ascii.h"
#include "comp.h"
#include "lib.h"

extern char* app_title;
extern char window_title[1024];

/* A way to delay rapid key pressing */ 
extern float key_tick;
extern float key_tick_max;
extern float key_tick_other;

extern bool running;

extern void yance_init();
