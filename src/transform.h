#pragma once

#include "Raquet.h"
#include "pixel.h"
#include "undo.h"

extern void transform_flip(SDL_FRect src);

extern void transform_mirror(SDL_FRect src);

extern void transform_translate(SDL_FRect src, int dir);

extern void transform_rotate(SDL_FRect src, int cw);