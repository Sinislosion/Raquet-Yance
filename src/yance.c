#include "yance.h"

char* app_title = "YANCE";
char window_title[1024];

bool running = true;

float key_tick = 0;
float key_tick_max = 30;
float key_tick_other = 0;

void yance_init() {
    ascii_init();
    comp_init();
}
