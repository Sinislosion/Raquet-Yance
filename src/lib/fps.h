#pragma once
#include "Raquet.h"

#define fps_avg_frame_total 16

extern float fps_avg;
extern float fps_avg_display;


extern uint32_t fps_tracker[fps_avg_frame_total];
extern uint32_t frame_counter;

extern void fps_update();
