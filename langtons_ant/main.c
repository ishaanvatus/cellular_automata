#include <stdio.h>
#include <stdlib.h>

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

    int width, height, frames; 

    //random coords just to put the ant somewhere in the top left:
    int ant_pos_x =  40%width;
    int ant_pos_y =  40%height;
    int dx = 0;
    int dy = -1;
    unsigned char plane[(width + 8 - 1)/8][height] = {};

    width = atoi(argv[1]);
    height = atoi(argv[2]);
    frames = atoi(argv[3]);

    for (int frame = 0; frame < frames; frame++) {
        char filename[31];
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
        sprintf(filename, "./frames/langton%05d.pbm", frame);
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
