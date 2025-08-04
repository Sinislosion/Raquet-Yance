#include "ascii.h"

SDL_Texture * ascii_texture;
Raquet_Rect ascii_rect;

void ascii_init() {
    int temp_w = 256 * ascii_char_width;

    ascii_rect = (Raquet_Rect) { 0, 0, temp_w, ascii_char_height };

    uint32_t* temp = malloc( temp_w * ascii_char_height * sizeof(int) );

    memset(temp, 0, sizeof(&temp));

    for ( int i = 0; i < 256; i++ ) {

        for ( int l = 0; l < ascii_char_height; l++ ) {
            unsigned char byte = __8x16font_bin[i * ascii_char_height + l];
            
            for ( uint16_t bit = 0; bit < ascii_char_width; bit++ ) {
                uint16_t b = 1 << bit;

                if ( bit >= 8 ) {

                    if ( i >= 0xc0 && i <= 0xdf ) {
                        b >>= 1;
                    } else {
                        b = byte = 0xff;
                    }

                }

                /* Create reference texture */

                int pixel = i * ascii_char_width + bit + l * temp_w;
                if ( !((unsigned char) b & byte) ) {
                    temp[pixel] = 0xffffffff;
                } else {
                    temp[pixel] = 0x00000000;
                }

            }

        }

    }

    ascii_texture = SDL_CreateTexture(
        Raquet_Renderer, 
        SDL_PIXELFORMAT_RGBA8888, 
        SDL_TEXTUREACCESS_STATIC, 
        temp_w, 
        ascii_char_height
    );

    SDL_SetTextureBlendMode(ascii_texture, SDL_BLENDMODE_BLEND);
    SDL_SetTextureScaleMode(ascii_texture, SDL_SCALEMODE_NEAREST);

    SDL_UpdateTexture(ascii_texture, NULL, temp, temp_w * sizeof(int));

}

void ascii_color_set(uint32_t color_value) {
    SDL_SetTextureColorMod(ascii_texture,
        color_value >> 24,
        color_value >> 16 & 0xff,
        color_value >> 8 & 0xff
    );
}


void ascii_text_render(unsigned char* text, int x, int y) {
    
    /*
     * Gets the ascii letter from the texture and
     * plots it onto the screen. Repeat for every
     * letter in the given string
     * 
     */

    int length = strlen((char*) text);
    Raquet_Rect src = { 0, 0, ascii_char_width, ascii_char_height };
    Raquet_Rect dest = { x, y, ascii_char_width, ascii_char_height };
    
    for ( int i = 0; i < length; i++ ) {
        int id = (int) text[i];
        src.x = id * ascii_char_width;
        dest.x = i * ascii_char_width + x;
        SDL_RenderTexture(Raquet_Renderer, ascii_texture, &src, &dest);
    }
}
