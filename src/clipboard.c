#include "clipboard.h"

/*
	yance clipboard structure

	offset  meaning
	------  -------
	0-4     "YANCE"
	5       type ("p" = pixels)
	6-9     count of pixels in 16bit base16
	a-b     width of pixels in 8bit base16
	c-n     data in 4bit base16
	n+1     \0 (string null terminator)
*/

void clipboard_pixels_copy(SDL_FRect src) {
	pixel_struct pxl = pixel_new();
	pxl.rect = src;
	SDL_SetClipboardText(pixel_state_capture(pxl));
}


void clipboard_pixels_cut(SDL_FRect src) {
	pixel_struct pxl = pixel_new();
	pxl.rect = src;
	undo_record(pixel_state_capture(pxl));
	SDL_SetClipboardText(pixel_state_capture(pxl));
	pxl.size = pxl.rect.w * pxl.rect.h;
	free(pxl.values);
	pxl.values = malloc(pxl.size);
	for (int i = 0; i < pxl.size; i++) {
		pxl.values[i] = 0;
	}
	pixel_state_plot(pxl);
}


void clipboard_pixels_paste(SDL_FRect dest) {
	pixel_struct pxl = pixel_new();
	char * string = SDL_GetClipboardText();
	int status = pixel_state_reconstruct(&pxl, string);
	SDL_free(string);
	if (status > 0) return;
	pxl.rect.x = dest.x;
	pxl.rect.y = dest.y;
	
	// store undo information
	pixel_struct pxl_undo = pixel_new();
	pxl_undo.rect = pxl.rect;
	undo_record(pixel_state_capture(pxl_undo));

	// plot clipboard to rom
	pixel_state_plot(pxl);
}