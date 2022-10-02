//my implementation of game of life in c
#include <stdio.h>
#include <stdlib.h>
int update(int grid_w, int grid_h, int grid[][grid_w], int buffer_grid[][grid_w], int heatmap[][grid_w]);
int survives(int grid_w, int grid_h, int row, int col, int grid[][grid_w]);
int double_buffer(int grid_w, int grid_h, int grid[][grid_w], int buffer_grid[][grid_w]);
int create_netpbm(char *name, int image_w, int image_h, int image[][image_w], int max, int mode);
int normalize(int image_w, int image_h, int heatmap[][image_w], int gens);
int double_buffer(int grid_w, int grid_h, int grid[][grid_w], int buffer_grid[][grid_w])
{
	for (int row = 0; row < grid_h; row++)
	{
		for (int col = 0; col < grid_w; col++)
		{
			buffer_grid[row][col] = grid[row][col];
		}
	}
}

int update(int grid_w, int grid_h, int grid[][grid_w], int buffer_grid[][grid_w], int heatmap[][grid_w])
{
	for (int row = 0; row < grid_h; row++)
	{
		for (int col = 0; col < grid_w; col++)
		{
			if (survives(grid_w, grid_h, row, col, buffer_grid))
			{
				grid[row][col] = 1;
				heatmap[row][col] += 1.0;
			}

			else
			{
				grid[row][col] = 0;
			}
		}
	}
}

int survives(int grid_w, int grid_h, int row, int col, int grid[][grid_w])
{
	//counting number of neighbors
	//Moore neighborhood
	int neighbors = 0;
	for (int r_off = -1; r_off <= 1; r_off++)
	{
		for (int c_off = -1; c_off <= 1; c_off++)
		{
			if ((r_off == c_off) && (r_off == 0))
			{
				continue;
			}

			else
			{
				neighbors += grid[(row + r_off + grid_h)%grid_h][(col + c_off + grid_w)%grid_w];
			}
		}
	}

	//Checking whether the cell stays alive or dies
	int alive = grid[row][col];
	return (((alive && ((neighbors == 2) || (neighbors == 3)))) || ((!alive) && (neighbors == 3)));
}
int create_netpbm(char *name, int image_w, int image_h, int image[][image_w], int max, int mode)
{
	FILE* pbmimg;
	pbmimg = fopen(name, "wb");
	fprintf(pbmimg, "P%d\n", mode); 
	fprintf(pbmimg, "%d %d\n", image_w, image_h); 
	
	fprintf(pbmimg, "%d\n", max); 
	for (int row = 0; row < image_h; row++)
	{
	    for (int col = 0; col < image_w; col++)
	    {
	        fprintf(pbmimg, "%d ", image[row][col]);
	    }
	    fprintf(pbmimg, "\n");
	}
	fclose(pbmimg);
}

int normalize(int image_w, int image_h, int heatmap[][image_w], int gens)
{
		for (int row = 0; row < image_h; row++)
		{
		    for (int col = 0; col < image_w; col++)
		    {
				heatmap[row][col] = (int) (((( (float) heatmap[row][col] )/(( (float) gens )))*255.0));
				//prevent inversion of image (else dead cells show as black pixels)
				heatmap[row][col] -= 255;
		    }
		}
}

int main(int argc, char **argv)
{
	//getting command line options
	int grid_w = atoi(argv[1]);
	int grid_h = atoi(argv[2]);
	int gens = atoi(argv[3]);
	
	int grid[grid_h][grid_w];
	int buffer_grid[grid_h][grid_w];
	int heatmap[grid_h][grid_w];
	
	//setting the entire grid and buffer grid to random state cells
	for (int row = 0; row < grid_h; row++)
	{
		for (int col = 0; col < grid_w; col++)
		{
			grid[row][col] = rand()%2;
			heatmap[row][col] = 0;
		}
	}

	int curr_gen = 0;
	char img_name[10];
	while (curr_gen < gens)
	{
		snprintf(img_name, 10, "%05d.pbm", curr_gen);
		create_netpbm(img_name, grid_w, grid_h, grid, 1, 1);

		double_buffer(grid_w, grid_h, grid, buffer_grid);
		update(grid_w, grid_h, grid, buffer_grid, heatmap); 

		curr_gen += 1;
	}
	normalize(grid_h, grid_h, heatmap, gens);
	create_netpbm("heatmap.pgm", grid_w, grid_h, grid, 255, 2);
}
