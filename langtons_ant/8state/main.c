#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <string.h>

#include "pam.h"

#define ALIVE 0
#define DEAD 1
void rotate(int *dx, int *dy, int dir);
int write_plane(char *filename, int width, int height, unsigned char plane[width][height]);

int main(int argc, char **argv)
{
    if (argc < 4) {
        fprintf(stderr, "Program Usage: ./main <width> <height> <generations>\n");
        return -1;
    }
    int palatte[8] = {
        0xFFFFFF, // dead,  up 
        0xFF00FF, // dead,  right 
        0xFF0F0F, // dead,  down 
        0xFFFF00, // dead,  left 
                  //
        0x000000, // alive, up 
        0x00FF00, // alive, right 
        0x00F0F0, // alive, down 
        0x0000FF, // alive, left
    };
    int width, height, frames; 
    width = atoi(argv[1]);
    height = atoi(argv[2]);
    frames = atoi(argv[3]);
    //random coords just to put the ant somewhere in the top left:
    int ant_pos_x =  40%width;
    int ant_pos_y =  40%height;
    int dx = 0;
    int dy = -1;
    uint8_t *raster;
    raster = malloc((size_t) 3*width*height);
    if (raster == NULL) {
        fprintf(stderr, "Couldn't allocate memory to raster\n");
        return 1;
    }
    memset(raster, 255, 3*width*height);
    for (int frame = 0; frame < frames; frame++) {
        char filename[31];
        int ant_index_red = ant_pos_y*width*3 + ant_pos_x*3;
        sprintf(filename, "./frames/langton%05d.pam", frame);
        FILE *fp = fopen(filename, "w");
        if (fp == NULL) {
            fprintf(stderr, "Couldn't create file \"%s\"", filename);
            return 1;
        }
        uint8_t mask = 0xFF;
        int state;
        if ((mask & raster[ant_index_red]) == 0)
            state = ALIVE;
        else 
            state = DEAD;
        int bit1 = (dx != 0)? 1 : 0;
        int bit2 = ((dy - dx) > 0)? 1 : 0;
        state = (state << 2) | (bit2 << 1) | bit1;
        int color = palatte[state];
        for (int channel = 0; channel < 3; channel++)
            raster[ant_index_red + channel] = color >> (3 - channel - 1)*8;
        if (state < 4)
            rotate(&dx, &dy, 1);
        else
            rotate(&dx, &dy, -1);
        ant_pos_x += dx;
        ant_pos_y += dy;
        ant_pos_x = ant_pos_x%width;
        ant_pos_y = ant_pos_y%height;
        write_pam(fp, width, height, 3, 8, raster);
        fclose(fp);
    }
    return 0;
}
void rotate(int *dx, int *dy, int dir) 
{
    int x = *dx;
    int y = *dy;
    *dx = dir*(-y);
    *dy = dir*(x);
}
