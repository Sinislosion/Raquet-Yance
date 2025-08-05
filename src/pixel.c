#include "pixel.h"

pixel_struct pixel_new() {
	pixel_struct pxl;
	pxl.values = NULL;
	return pxl;
}

// convert pixel data to clipboard data
const char* pixel_state_capture(pixel_struct pxl) {
	int size = pxl.rect.w * pxl.rect.h;
	char * string = malloc((0xc + size + 1) * sizeof(char*));
	char * pout = string;
	const char * hex = "0123456789abcdef";
	// identifier
	strcpy(string, "YANCEp");
	pout += 6;
	// x pos in 8bits base16
	*pout++ = hex[((uint8_t) pxl.rect.x >> 4) & 0xf];
	*pout++ = hex[(uint8_t) pxl.rect.x & 0xf];
	// y pos in 16bits base16
	*pout++ = hex[((uint16_t) pxl.rect.y >> 12) & 0xf];
	*pout++ = hex[((uint16_t) pxl.rect.y >> 8) & 0xf];
	*pout++ = hex[((uint16_t) pxl.rect.y >> 4) & 0xf];
	*pout++ = hex[(uint16_t) pxl.rect.y & 0xf];
	// width in 8bits base16
	*pout++ = hex[((uint8_t) pxl.rect.w >> 4) & 0xf];
	*pout++ = hex[(uint8_t) pxl.rect.w & 0xf];
	// height in 16bits base16
	*pout++ = hex[((uint16_t) pxl.rect.h >> 12) & 0xf];
	*pout++ = hex[((uint16_t) pxl.rect.h >> 8) & 0xf];
	*pout++ = hex[((uint16_t) pxl.rect.h >> 4) & 0xf];
	*pout++ = hex[(uint16_t) pxl.rect.h & 0xf];
	// pixel data from rom data
	free(pxl.values);
	pxl.values = malloc(size);
	for (int i = 0; i < size; i++) {
		pxl.values[i] = table_pixel_get_value(pxl.rect.x + (i % (int)pxl.rect.w), pxl.rect.y + (i / pxl.rect.w));
	}
	// pixel data in 4bit base16
	for (int i = 0; i < size; i++) *pout++ = hex[pxl.values[i] & 0xf];
	// null terminator
	*pout++ = '\0';
	pout = string;
	return string;
}

// plot pixel data to main table view
void pixel_state_plot(pixel_struct pxl) {
	for (int i = 0; i < pxl.size; i++) {
		table_pixel_set_value(pxl.rect.x + (i % (int)pxl.rect.w), pxl.rect.y + (i / pxl.rect.w), pxl.values[i]);
	}
}

// read pixel data to main chr buffer
void pixel_state_read(pixel_struct pxl, char* str) {
	const char* hex = "0123456789abcdef";
	for (int i = 0; i < pxl.size; i++) {
		str[0x12 + i] = hex[table_pixel_get_value(pxl.rect.x + (i % (int)pxl.rect.w), pxl.rect.y + (i / pxl.rect.w)) & 0x03];
	}
}

// convert clipboard data to pixel data
int pixel_state_reconstruct(pixel_struct* pxl, char* str) {
	// identifier
	const char* ident = "YANCEp";
	for (unsigned long long i = 0; i < strlen(ident); i++) {
		if (str[i] != ident[i]) return 1;
	}
	// total pixels in 16bit base16
	char buff[5];
	// y pos in 16bits base16
	memcpy(buff, &str[0x08], 4);
	pxl->rect.y = (int) strtol(buff, NULL, 16);
	// height in 16bits base16
	memcpy(buff, &str[0x0e], 4);
	pxl->rect.h = (int) strtol(buff, NULL, 16);
	// x pos in 8bits base16
	memcpy(buff, &str[0x6], 2);
	buff[2] = '\0';
	pxl->rect.x = (int) strtol(buff, NULL, 16);
	// width in 8bits base16
	memcpy(buff, &str[0xc], 2);
	pxl->rect.w = (int) strtol(buff, NULL, 16);
	// set size
	pxl->size = pxl->rect.w * pxl->rect.h;
	// pixel data in 4bit base16
	buff[1] = '\0';
	free(pxl->values);
	pxl->values = malloc(pxl->size);
	for (int i = 0; i < pxl->size; i++) {
		memcpy(buff, &str[0x12 + i], 1);
		pxl->values[i] = (uint8_t) strtol(buff, NULL, 16);
	}
	return 0;
}