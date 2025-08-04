#include "status_bar.h"

int comps_status_bar_counter = 0;
char comps_status_bar_message[256];

void comps_status_bar_message_set(const char* message) {
    comps_status_bar_counter = 120;
    strcpy(comps_status_bar_message, message);
}

void comps_status_bar_render() {
    Raquet_Rect status_rect = { 0, SCREEN_HEIGHT - 16, SCREEN_WIDTH, 16 };
    
    Raquet_DrawRectangle(
        status_rect.x, 
        status_rect.y, 
        status_rect.w, 
        status_rect.h, 
        RQ_PAL(0x01), 
        255, 
        true
    );
    
    if ( comps_status_bar_counter ) {
    
        ascii_color_set(RQ_PAL(0x30));
        ascii_text_render( (unsigned char*) comps_status_bar_message, 0, status_rect.y );
    
    } else {

        /* STATUS BAR DEFAULT */
        unsigned char status_text[256];

        /* text */
        ascii_color_set(RQ_PAL(0x30));
        sprintf( 
            (char*) status_text,
            " $%04x   TILE COUNT: %d    ROM SIZE: %d bytes    %s    FPS: %7.3f",
            pos_addr,
            rom_tile_count,
            file_chr_rom_size,
            header_type_str,
            fps_avg_display
        );
        ascii_text_render(status_text, 0, status_rect.y);
    }

    /* Help notice */
    ascii_text_render( (unsigned char*)"F1 for Help!", SCREEN_WIDTH - 13 * 9, status_rect.y );

    comp_space.h -= 16;

}
