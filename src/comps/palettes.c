#include "palettes.h"

void comps_palettes_render(int x_cen, int y_cen) {
	// draw all palettes
	int swatch_size = 16;
	int x_off = x_cen - 2 * swatch_size;
	int y_off = y_cen - 4 * swatch_size;
	for (int pal = 0; pal < 8; pal++) {
		for (int col = 0; col < 4; col++) {
			int color_id = palette[pal][col];
			if (col == 0) color_id = palette[0][0];
			Raquet_SetDrawColor(RQ_PAL(color_id), 255);
			SDL_RenderFillRect(Raquet_Renderer, &(SDL_FRect) {
				x_off + col * (swatch_size + 1),
				y_off + (pal * (swatch_size + 1)),
				swatch_size, swatch_size,
			});
		}
	}
	// highlight current palette
	Raquet_SetDrawColor(RQ_PAL(0x26), 255);
	SDL_RenderRect(Raquet_Renderer, &(SDL_FRect) { 
		x_off - 1, y_off + (swatch_size + 1) * palette_current, 
		4 * (swatch_size + 1) + 2, swatch_size
	});
	SDL_RenderRect(Raquet_Renderer, &(SDL_FRect) { 
		x_off, y_off + (swatch_size + 1) * palette_current - 1, 
		4 * (swatch_size + 1), swatch_size + 2
	});
	// highlight current color
	Raquet_SetDrawColor(RQ_PAL(0x30), 255);
	SDL_RenderRect(Raquet_Renderer, &(SDL_FRect) { 
		x_off - 1 + (swatch_size + 1) * palette_current_color,
		y_off + (swatch_size + 1) * palette_current,
		swatch_size + 2, swatch_size
	});
	SDL_RenderRect(Raquet_Renderer, &(SDL_FRect) { 
		x_off + (swatch_size + 1) * palette_current_color,
		y_off - 1 + (swatch_size + 1) * palette_current,
		swatch_size, swatch_size + 2
	});
}