#include "../lib/fps.h"
#include "../comp.h"
#include "../ascii.h"
#include "../table.h"

extern int comps_status_bar_counter;
extern char comps_status_bar_message[256];

extern void comps_status_bar_message_set(const char* message);

extern void comps_status_bar_render();
