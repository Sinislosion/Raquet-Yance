#include "yance.h"
#include "comp.h"
#include "comps/manual.h"
#include "comps/rom_table.h"
#include "comps/status_bar.h"
#include "comps/colors.h"

Raquet_Rect comp_space;

Raquet_Point table_cursor;
Raquet_Rect table_selection;
Raquet_Point table_selection_origin;

Raquet_Point editor_cursor;
Raquet_Rect editor_selection;
Raquet_Point editor_selection_origin;

int pos_addr;

comp_targets comp_target;

void comp_init() {
    comp_target = rom_table;
    Raquet_Point point = { 0, 0 };
    Raquet_Rect rect = { 0, 0, 1, 1 };

    table_cursor = point;
    table_selection = rect;
    table_selection_origin = point;

    editor_cursor = point;
    editor_selection = rect;
    editor_selection_origin = point;

    pos_addr = 0;
    comps_manual_init();

}

void comp_render() {

    Raquet_Clear(RQ_PAL(0x2D));

    /* Setup comp space and render comps */
    comp_space = (Raquet_Rect) { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };

    comps_status_bar_render();

    comps_rom_table_render();

    comps_colors_render();
    // TODO: comps_editor_render()
    
    if (comp_target == manual) {
        comps_manual_render();
    }

}

void comp_update() {

    /* Bring up help menu */
    if (Raquet_KeyCheck(SDL_SCANCODE_F1)) {
        comps_manual_set_as_target();
    }

    /* Quitting */
    if (Raquet_KeyCheck(SDL_SCANCODE_LCTRL) && Raquet_KeyCheck(SDL_SCANCODE_Q)) {
        running = false;
    }

    /* Tab around */
    if (Raquet_KeyCheck_Pressed(SDL_SCANCODE_TAB)) {
        comp_target++;
        if (comp_target > 1) {
            comp_target = 0;
        }
    }

    /* Save */
    if (Raquet_KeyCheck(SDL_SCANCODE_LCTRL) && Raquet_KeyCheck(SDL_SCANCODE_S)) {
        table_save();
    }

    /* Import BMP */
    if (Raquet_KeyCheck(SDL_SCANCODE_LCTRL) && Raquet_KeyCheck(SDL_SCANCODE_B)) {
		SDL_Surface* bmp_surface = bmp_get_surface(Raquet_AbsoluteToAsset("yance-default-tilese-2t.bmp"));

        printf("bmp x,y : %d, %d \n", bmp_surface->w, bmp_surface->h);
		printf("bmp bpp: %f\n", (float) bmp_surface->pitch / (float) bmp_surface->w);

		for (int y = 0; y < bmp_surface->h; y++) {
			for (int x = 0; x < bmp_surface->w; x++) {
				SDL_Color rgb = bmp_get_color(bmp_surface, x, y);
				int avg = ((rgb.r + rgb.g + rgb.b) / 3) >> 6;
				table_pixel_set_value(x, y, avg);

			}
		}
	}

    if (Raquet_KeyCheck(SDL_SCANCODE_LCTRL) && !Raquet_KeyCheck(SDL_SCANCODE_LSHIFT)) {
        for (int i = SDL_SCANCODE_1; i <= SDL_SCANCODE_8; i++) {
            if (Raquet_KeyCheck_Pressed(i)) {
                palette_current_set(i - SDL_SCANCODE_1);
                table_update_palette();
                break;
            }
        }

        if (key_can_go()) {
            int color_target = palette_current_color_id; 
            if (Raquet_KeyCheck(SDL_SCANCODE_RIGHT)) {
                if ((color_target & 0x0F) < 0x0F) {
                    color_target++;
                }
            }

            if (Raquet_KeyCheck(SDL_SCANCODE_LEFT)) {
                if ((color_target & 0x0F) > 0x00) {
                    color_target--;
                }
            }

            if (color_target != palette_current_color_id) {
                if (color_target < 0x00) {
                    color_target = 0x00;
                }

                if (color_target > 0x3F) {
                    color_target = 0x3F;
                }

                palette_current_color_value_set(color_target);
                table_update_palette();
            }
        }

    

    }

    switch (comp_target) {
        case rom_table:
            comps_rom_table_update();
            break;

        case editor:

            break;

        case manual:
            comps_manual_update();
            break;
    }

}
