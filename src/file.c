#include "file.h"

uint8_t* header;
char header_type_str[16];

file_types file_type;

char* file_filename;

int file_has_trainer;
int file_prg_rom_size;
int file_chr_rom_size;
int file_chr_rom_start;

void file_set_filename(char* filename) {

    free(file_filename);
    file_filename = malloc(strlen(filename));

    strcpy(file_filename, filename);

    strcpy(window_title, app_title);
    strcat(window_title, " - ");
    strcat(window_title, filename);

    SDL_SetWindowTitle(Raquet_Window, window_title);
    
}

void file_load(char* filename) {

    file_set_filename(filename);

    FILE* file = fopen(filename, "rb");

    header = malloc(sizeof(uint8_t) * 16);

    int err = fread(header, 16, 1, file);
    printf("Status of %s: %d\n", filename, err);

    /* Zero out file properties */
    file_type = unknown;
    file_has_trainer = 0;
    file_prg_rom_size = 0;
    file_chr_rom_size = 0;
    file_chr_rom_start = 0;

    strcpy(header_type_str, "NO HEADER");

    if (header[0] == 'N' && header[1] == 'E' && header[2] == 'S' && header[3] == 0x1A) {
        file_type = iNES;
        strcpy(header_type_str, "iNES");
        file_prg_rom_size = header[4] << 14;
        file_chr_rom_size = header[5] << 13;

        if (header[6] & 0x04) {
            file_has_trainer = 512;
        }

        if ((header[7] & 0x0C) == 0x08) {
            file_type = NES2;
            strcpy(header_type_str, "NES2.0");
        }
        file_chr_rom_start = 16 + file_has_trainer;
        
        if (file_chr_rom_size) {
            file_chr_rom_start += file_prg_rom_size;
        } else {
            file_chr_rom_size = file_prg_rom_size;
        }

    } else if ( header[0] == 'P' && header[1] == 'P' && header[2] == 'F' && header[3] == 'v' && header[4] == 1) {
        file_type = PPF;
        strcpy(header_type_str, "PPF v1.0");
        fseek(file, 0, SEEK_END);
        file_chr_rom_size = ftell(file);
    } else {
        fseek(file, 0, SEEK_END);
        file_chr_rom_size = ftell(file);
    }
    fclose(file);
    free(header);

}
