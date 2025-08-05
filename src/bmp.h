#pragma once
#include "Raquet.h"

extern SDL_Surface* bmp_get_surface(const char* filename);

extern uint32_t bmp_get_pixel(SDL_Surface* surface, int x, int y);

extern SDL_Color bmp_get_color(SDL_Surface* surface, int x, int y);