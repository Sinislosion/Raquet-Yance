#pragma once

#include "pixel.h"

#define undo_max_steps 256

extern char** undo_log;
extern int undo_head;
extern int undo_tail;
extern int undo_top;

extern void undo_init(void);

extern void undo_record(const char* data);

extern int undo_rewind(void);

extern int undo_forward(void);