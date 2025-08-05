// put your libs here.
#include "Raquet.h"

#include "yance.h"
#include "table.h"


void createthedog(void) {

    yance_init();
    table_load((char*)Raquet_AbsoluteToAsset("guntner.chr")); 

}

void runthedog(void) {

    comp_render();

    lib_update();
    comp_update();

    if (running == false) {
        SDL_Event ev;
	    ev.type = SDL_EVENT_QUIT;
	    SDL_PushEvent(&ev);
    }

    bool did_hit = false;

    for (int i = 0; i < SDL_SCANCODE_COUNT; i++) {
        if (Raquet_SDLKeys[i] != 0 && i != SDL_SCANCODE_LSHIFT && i != SDL_SCANCODE_LCTRL) {
            key_tick += (Raquet_DeltaTime / 5);
            key_tick_other += (Raquet_DeltaTime / 5);
            did_hit = true;
            break;
        } 
    }

    if (did_hit == false) { 
        key_tick = 0;
    }

}

int main(void) {
    Raquet_Main();
    return 0;
}
