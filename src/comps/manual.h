#include "../comp.h"

extern comp_targets comps_manual_cache_src_comp; // TODO:: figure out wtf this means

/*
 * Minimum screen size is 640x480
 * Font size is 9x16
 * 71x30 characters on minimum window
 * for centering and status bar: 70x28 character grid
 */

#define manual_rows 28
#define manual_cols 70

extern Raquet_Rect manual_rect;

extern unsigned char manual_screen[manual_rows][manual_cols + 1];

extern char manual_commands_global[][65];

extern void comps_manual_set_as_target();

extern void comps_manual_init();

extern void comps_manual_render();

extern void comps_manual_update();
