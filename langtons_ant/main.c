#include <stdio.h>
#include <stdlib.h>

void rotate(int *dx, int *dy, int dir);
int write_plane(char *filename, int width, int height, char plane[width][height]);
int main(int argc, char **argv)
{
    if (argc < 3) {
        fprintf(stderr, "Program Usage: ./main <width> <height>\n");
        return -1;
    }
    int width, height;
    width = atoi(argv[1]);
    height = atoi(argv[2]);

    int ant_pos_x = width/2;
    int ant_pos_y = height/2;
    int dx = 1;
    int dy = 0;

    char plane[width/8][height] = {};

    for (int frame = 0; frame < 200; frame++) {
        char filename[15];
        sprintf(filename, "langton%03d.pbm", frame);
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
int write_plane(char *filename, int width, int height, char plane[width][height])
{
    FILE* fp = fopen(filename, "w+");
    if (fp == NULL) {
        fprintf(stderr, "Failed to open file\n");
        return -1;
    }
    fprintf(fp, "P4\n");
    fprintf(fp, "%d %d\n", width, height);
    for (int row = 0; row < height; row ++) {
        for (int col = 0; col < width/8; col++) {
            fwrite(&plane[col][row], sizeof(plane[0][0]), 1, fp);
        }
    }
    fclose(fp);
    return 0;
}
