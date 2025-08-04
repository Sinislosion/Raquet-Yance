#pragma once
#include "yance.h"
#include <string.h>
#include <stdlib.h>

extern uint8_t* header;
extern char header_type_str[16];

typedef enum file_types {
    unknown,
    iNES,
    NES2,
    PPF
} file_types;

extern file_types file_type;

extern char* file_filename;
extern int file_has_trainer;
extern int file_prg_rom_size;
extern int file_chr_rom_size;
extern int file_chr_rom_start;

extern void file_set_filename(char* filename);

extern void file_load(char* filename);
