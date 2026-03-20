#include <stdio.h>
#include <stdlib.h>
#define ALIVE 1
#define DEAD 0
void rotate(int *dx, int *dy, int dir);
int write_plane(char *filename, int width, int height, unsigned char plane[width][height]);
int main(int argc, char **argv)
{
    if (argc < 4) {
        fprintf(stderr, "Program Usage: ./main <width> <height> <generations>\n");
        return -1;
    }
    int width, height, frames;
    width = atoi(argv[1]);
    height = atoi(argv[2]);
    frames = atoi(argv[3]);
    int ant_pos_x = width/2;
    int ant_pos_y = height/2;
    int dx = 1;
    int dy = 0;

    unsigned char plane[(width + 8 - 1)/8][height] = {};
    /*
    for (int row = 0; row < height; row ++) {
        for (int col = 0; col < (width + 8 - 1)/8; col++) {
            plane[col][row] = rand()%256;
        }
    }
    */
    for (int frame = 0; frame < frames; frame++) {
        char filename[17];
        int offset = 7 - ant_pos_x%8;
        unsigned char cell_status = (plane[ant_pos_x/8][ant_pos_y] >> offset) & 0x01;
        if (cell_status == DEAD) {
            rotate(&dx, &dy, 1);
        }
        else {
            rotate(&dx, &dy, -1);
        }
        int mask = 0x1 << offset;
        plane[ant_pos_x/8][ant_pos_y] = plane[ant_pos_x/8][ant_pos_y] ^ mask;
        ant_pos_x += dx;
        ant_pos_y += dy;
        ant_pos_x = ant_pos_x%width;
        ant_pos_y = ant_pos_y%height;
        sprintf(filename, "langton%05d.pbm", frame);
        write_plane(filename, width, height, plane);
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
int write_plane(char *filename, int width, int height, unsigned char plane[width][height])
{
    FILE* fp = fopen(filename, "w+");
    if (fp == NULL) {
        fprintf(stderr, "Failed to open file\n");
        return -1;
    }
    fprintf(fp, "P4\n");
    fprintf(fp, "%d %d\n", width, height);
    for (int row = 0; row < height; row ++) {
        for (int col = 0; col < (width + 8 - 1)/8; col++) {
            fwrite(&plane[col][row], sizeof(plane[0][0]), 1, fp);
        }
    }
    fclose(fp);
    return 0;
}
