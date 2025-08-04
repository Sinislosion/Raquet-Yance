#include "manual.h"
#include "../ascii.h"

comp_targets comps_manual_cache_src_comp;

Raquet_Rect manual_rect = { 
    0, 0, 
    manual_cols * 9, manual_rows * 16 
};

unsigned char manual_screen[manual_rows][manual_cols + 1];

char manual_commands_global[][65] = {
    "             Yet  Another  NES  CHR  Editor  Manual            ",
	"                                                                 ",
	"                             ",
	"    Open        Drag + Drop     Navigate          Tab",
	"    New         tbd Ctrl-N   ",
	"    Save        Ctrl-S          Move Cursor       Arrows",
	"                                                             ",
	"    Copy        Ctrl-C          Edit Selection    Shift-Arrows",
	"    Cut         Ctrl-X                        ",
	"    Paste       Ctrl-V          Deselect          Ctrl-D",
	"",
	"    Undo        Ctrl-Z          Page Up/Down in Rom View",
	"    Redo        Ctrl-Y          Toggle 8x16 Mode  T",
	"                                Plot Pixels       Space",
	"",
	"    Flip        F               Current Color     1,2,3,4",
	"    Mirror      M               Change Color      Ctrl-Arrows",
	"    Translate   CtrlShftArrows  Current Palette   Ctrl-(1..8)",
	"    Rotate CW   R               Grid Toggle       G",
	"    Rotate CCW  Shift-R         View Source       Ctrl-G",
	"",
	"",
	"    Quit        Ctrl-Q                 Close this Manual   ESC",
	"",
};

void comps_manual_set_as_target() {
    if (comp_target != manual) {
        comps_manual_cache_src_comp = comp_target;
        comp_target = manual;
    }
}

void comps_manual_init() {
    for ( int row = 0; row < manual_rows; row++ ) {

        for ( int col = 0; col < manual_cols; col++ ) {
            
            if ( col == 0 || col == manual_cols - 1 ) {
                manual_screen[row][col] = 0xba; // what is this meant to address?
            
            } else if ( row == 0 || row == manual_rows - 1 ) {
                manual_screen[row][col] = 0xcd;
            
            } else {
                manual_screen[row][col] = 0x20;

            }

        }

    }

    /* I think these are meant to be corners and stuff */
    manual_screen[0][0] = 0xc9;
    manual_screen[0][manual_cols - 1] = 0xbb;

    manual_screen[manual_rows - 1][0] = 0xc8;
    manual_screen[manual_rows - 1][manual_cols - 1] = 0xbc;

    for ( int row = 0; row < 24; row++ ) {
        
        for ( int col = 0; col < 64; col++ ) {
            
            if ((int) manual_commands_global[row][col] != 0 ) {
                manual_screen[row + 2][col + 3] = (unsigned char) manual_commands_global[row][col];
            }

        }
    
    }

    // THIS IS TO TEST DO NOT UNCOMMENT OR YOU WILL DIE
    /*for (int i = 0; i < manual_rows; i++) {
        printf("%s\n", manual_screen[i]);
    }*/

}

Raquet_Rect window_rect = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};

void comps_manual_render() {
    manual_rect.x = (window_rect.w - manual_rect.w) / 2;
    manual_rect.y = (window_rect.h - manual_rect.h) / 2 - 8;

    Raquet_DrawRectangle(manual_rect.x, manual_rect.y, manual_rect.w, manual_rect.h, RQ_PAL(0x00), 255, true);
    
    ascii_color_set(RQ_PAL(0x30));

    for ( int i = 0; i < manual_rows; i++ ) {
        ascii_text_render(manual_screen[i], manual_rect.x, manual_rect.y + i * 16);
    }

}

void comps_manual_update() {
    if (Raquet_KeyCheck(SDL_SCANCODE_ESCAPE)) {
        comp_target = comps_manual_cache_src_comp;
    }
}

