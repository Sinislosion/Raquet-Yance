#include "Raquet.h"
#include "../comp.h"
#include "../table.h"
#include "../tile.h"
#include "rom_table.h"

int table_scroll_pos = 0;

void comps_rom_table_render() {

	// add top/left/bottom margins
	comp_space.x += 8;
	comp_space.w -= 8;
	comp_space.y += 8;
	comp_space.h -= 16;

	// tile size
	int tile_size = (SCREEN_WIDTH > 1024) ? 24 : 16;
	tile_rect.w = tile_rect.h = tile_size;

	// scrolling calculations
	int rows_start = 0;
	int rows_total = (int) ceilf((float) rom_tile_count / 16.f);
	int rows_visible = comp_space.h / tile_size;
	rows_visible = (rows_total < rows_visible) ? rows_total : rows_visible;
	if (table_selection.y - table_scroll_pos < 4) {
		table_scroll_pos = table_selection.y - 4;
		if (table_scroll_pos < 0) table_scroll_pos = 0;
	}
	int select_bottom = table_selection.y + table_selection.h;
	if (select_bottom - rows_visible > table_scroll_pos - 4) {
		table_scroll_pos = select_bottom + 4 - rows_visible;
		if (table_scroll_pos + rows_visible > rows_total) {
			table_scroll_pos = rows_total - rows_visible;
		}
	}

	// RENDER VISIBLE TILES
	int i = 0;
	int tile_start = (table_scroll_pos + rows_start) << 4;
	int tile_end = tile_start + (rows_visible << 4);
	for (int t = tile_start; t < tile_end; t++) {
		tile_rect.x = comp_space.x + (i % 16) * tile_size;
		tile_rect.y = comp_space.y + (i >> 4) * tile_size;
		int tile_id = table_sprite_size_mode_translate(t);
		SDL_RenderTexture(Raquet_Renderer, table_tiles[tile_id].texture, NULL, &tile_rect);
		i++;
	}

	// HIGHLIGHT COMP (if current)
	if (comp_target == rom_table) {
		Raquet_SetDrawColor(RQ_PAL(0x26), 255);
		SDL_RenderRect(Raquet_Renderer, &(SDL_FRect) {
			comp_space.x - 3,
			comp_space.y - 1,
			(tile_size << 4) + 6,
			tile_size * rows_visible + 2,
		});
		SDL_RenderRect(Raquet_Renderer, &(SDL_FRect) {
			comp_space.x - 2,
			comp_space.y - 2,
			(tile_size << 4) + 4,
			tile_size * rows_visible + 4,
		});
		SDL_RenderRect(Raquet_Renderer, &(SDL_FRect) {
			comp_space.x - 1,
			comp_space.y - 3,
			(tile_size << 4) + 2,
			tile_size * rows_visible + 6,
		});
	}


	// SHOW CURSOR
	if (Raquet_KeyCheck(SDL_SCANCODE_LSHIFT) && comp_target == rom_table) {
		Raquet_SetDrawColor(RQ_PAL(0x30), 255);
		SDL_RenderRect(Raquet_Renderer, &(SDL_FRect) { 
			6 + table_cursor.x * tile_size,
			7 + (table_cursor.y - table_scroll_pos) * tile_size,
			tile_size + 4,
			tile_size + 2,
		});
		SDL_RenderRect(Raquet_Renderer, &(SDL_FRect) { 
			7 + table_cursor.x * tile_size,
			6 + (table_cursor.y - table_scroll_pos) * tile_size,
			tile_size + 2,
			tile_size + 4,
		});
	}

	// SHOW SELECTION
	Raquet_SetDrawColor(RQ_PAL(0x30), 255);
	SDL_RenderRect(Raquet_Renderer, &(SDL_FRect) { 
		6 + table_selection.x * tile_size,
		7 + (table_selection.y - table_scroll_pos) * tile_size,
		table_selection.w * tile_size + 4,
		table_selection.h * tile_size + 2,
	});
	SDL_RenderRect(Raquet_Renderer, &(SDL_FRect) { 
		7 + table_selection.x * tile_size,
		6 + (table_selection.y - table_scroll_pos) * tile_size,
		table_selection.w * tile_size + 2,
		table_selection.h * tile_size + 4,
	});

	// adjust space
	int size = tile_size * 16 + 16;
	comp_space.x += size;
	comp_space.w -= size;
}


void comps_rom_table_update() {
	if (Raquet_KeyCheck(SDL_SCANCODE_LCTRL) && Raquet_KeyCheck(SDL_SCANCODE_D)) {
		table_selection.w = 1;
		table_selection.h = 1;
	}
	if (Raquet_KeyCheck(SDL_SCANCODE_PAGEUP)) {
		int diff = table_selection.y - 16;
		table_cursor.y -= 16;
		table_selection_origin.y -= 16;
		if (diff < 0) { 
			table_cursor.y -= diff;
			table_selection_origin.y -= diff;
		}
	}
	if (Raquet_KeyCheck(SDL_SCANCODE_PAGEDOWN)) {
		int diff = table_selection.y + table_selection.h + 16 - (rom_tile_count >> 4);
		table_cursor.y += 16;
		table_selection_origin.y += 16;
		if (diff > 0) { 
			table_cursor.y -= diff;
			table_selection_origin.y -= diff;
		}
	}
	if (!Raquet_KeyCheck(SDL_SCANCODE_LCTRL)) {
		if (Raquet_KeyCheck(SDL_SCANCODE_UP) && key_can_go() ) {
			if (Raquet_KeyCheck(SDL_SCANCODE_LSHIFT)) {
				if (table_cursor.y > 0) table_cursor.y--;
			}
			else if (table_selection.y > 0) {
				table_selection_origin.y--;
				table_cursor.y--;
			}
		}
		if (Raquet_KeyCheck(SDL_SCANCODE_DOWN) && key_can_go() ) {
			if (Raquet_KeyCheck(SDL_SCANCODE_LSHIFT)) {
				if (table_cursor.y < (rom_tile_count >> 4) - 1) table_cursor.y++;
			}
			else if (table_selection.y + table_selection.h < rom_tile_count >> 4) {
				table_selection_origin.y++;
				table_cursor.y++;
			}
		}
		if (Raquet_KeyCheck(SDL_SCANCODE_LEFT) && key_can_go() ) {
			if (Raquet_KeyCheck(SDL_SCANCODE_LSHIFT)) {
				if (table_cursor.x > 0) table_cursor.x--;
			}
			else if (table_selection.x > 0) {
				table_selection_origin.x--;
				table_cursor.x--;
			}
		}
		if (Raquet_KeyCheck(SDL_SCANCODE_RIGHT) && key_can_go() ) {
			if (Raquet_KeyCheck(SDL_SCANCODE_LSHIFT)) {
				if (table_cursor.x < 16 - 1) table_cursor.x++;
			}
			else if (table_selection.x + table_selection.w < 16) {
				table_selection_origin.x++;
				table_cursor.x++;
			}
		}
	}
	
	// calculate table selection quards
	if (table_cursor.x >= table_selection_origin.x) {
		table_selection.x = table_selection_origin.x;
		table_selection.w = table_cursor.x - table_selection_origin.x + 1;
	}
	else {
		table_selection.x = table_cursor.x;
		table_selection.w = table_selection_origin.x - table_cursor.x;
	}
	if (table_cursor.y >= table_selection_origin.y) {
		table_selection.y = table_selection_origin.y;
		table_selection.h = table_cursor.y - table_selection_origin.y + 1;
	}
	else {
		table_selection.y = table_cursor.y;
		table_selection.h = table_selection_origin.y - table_cursor.y;
	}

	// make sure editor_selection fits within table_selection
	int diff;
	diff = (((int)table_selection.w) << 3) - (editor_selection.x + editor_selection.w);
	if (diff < 0) editor_selection.x += diff;
	if (editor_selection.x < 0) {
		editor_selection.w += editor_selection.x;
		editor_selection.x = 0;
	}
	diff = (((int)table_selection.h) << 3) - (editor_selection.y + editor_selection.h);
	if (diff < 0) editor_selection.y += diff;
	if (editor_selection.y < 0) {
		editor_selection.h += editor_selection.y;
		editor_selection.y = 0;
	}
	pos_addr = table_sprite_size_mode_translate(table_selection.x + (((int)table_selection.y) << 4));
}

bool key_can_go() {
    if (key_tick == 0 || (key_tick_other > 10 && key_tick > key_tick_max)) {
        key_tick_other = 0;
        return true;
    }
    return false;
}
