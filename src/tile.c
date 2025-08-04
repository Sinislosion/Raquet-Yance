#include "tile.h"

Raquet_Rect tile_rect = { 0, 0, 8, 8 };

void tile_init(tile_struct* tile) {
    if ( !tile->color_data ) {

        tile->color_data = malloc( sizeof(uint32_t) * (tile_rect.w * tile_rect.h) );

        tile->texture = SDL_CreateTexture(
            Raquet_Renderer, 
            SDL_PIXELFORMAT_RGBA8888, 
            SDL_TEXTUREACCESS_STATIC, 
            tile_rect.w, 
            tile_rect.h
        );
        
        SDL_SetTextureBlendMode(tile->texture, SDL_BLENDMODE_BLEND);
        SDL_SetTextureScaleMode(tile->texture, SDL_SCALEMODE_NEAREST);
    
    }
}

void tile_update_texture(tile_struct* tile) {
    SDL_UpdateTexture(tile->texture, NULL, tile->color_data, tile_rect.w * sizeof(int));
}

void tile_update_pixel(tile_struct* tile, int pos, int value) {
    tile->values[pos] = value;
    tile->color_data[pos] = palette_rgb_get(palette_current, value);

    // TODO: add a queing system with a max amount of tiles updated per frame

    tile_update_texture(tile);
}

void _2bpp_to_tile(uint8_t data[16], tile_struct* tile) {
    tile->pal = 0;
    int pos = 0;
    for ( uint8_t l = 0; l < 8; l++ ) {
        
        uint8_t lo = data[l];
        uint8_t hi = data[8 + l];

        for ( uint8_t bit = 0; bit < 8; bit++ ) {
            uint8_t b = 1 << ( 7 - bit );
            
            uint8_t color = (lo & b) ? 1 : 0;
            
            color += (hi & b) ? 2 : 0;
        
            tile->values[pos] = color;

            tile->color_data[pos] = palette_rgb_get(tile->pal, color);

            pos++;
        }
    }
    tile_update_texture(tile);
}

void _tile_to_2bpp(tile_struct* tile, uint8_t data[16]) {
    
    memset(data, 0, 16);

    for ( int i = 0; i < 64; i++ ) {

        uint8_t bit_shifter = ( 7 - (i % 8) );
        uint8_t byte = i >> 3;

        data[byte] |= (tile->values[i] & (uint8_t) 1) << bit_shifter;
        data[byte + 8] |= ( (tile->values[i] & (uint8_t) 2) >> 1 ) << bit_shifter;

    }

}

