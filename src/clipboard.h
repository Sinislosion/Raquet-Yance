#pragma once

#include "Raquet.h"
#include "pixel.h"
#include "undo.h"

extern void clipboard_pixels_copy(SDL_FRect src);

extern void clipboard_pixels_cut(SDL_FRect src);

extern void clipboard_pixels_paste(SDL_FRect dest);