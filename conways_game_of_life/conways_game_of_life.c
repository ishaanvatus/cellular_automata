//my implementation of game of life in c
#include <stdio.h>
#include <stdlib.h>
int main(int argc, char **argv)
{
	int grid_w = atoi(argv[1]);
	int grid_h = atoi(argv[2]);
	int gens = atoi(argv[3]);

	int grid[grid_h][grid_w];
	int buffer_grid[grid_h][grid_w];
	float heatmap[grid_h][grid_w];
	
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
	while (curr_gen < gens)
	{

		//setting the entire buffer grid equal to the changed grid
		for (int row = 0; row < grid_h; row++)
		{
			for (int col = 0; col < grid_w; col++)
			{
				buffer_grid[row][col] = grid[row][col];
			}
		}
		//iterating over each cell in the grid
		for (int row = 0; row < grid_h; row++)
		{
			for (int col = 0; col < grid_w; col++)
			{
				int n_bors = 0;
				//counting the 8 neighbors of the cell
				for (int r_ofst = -1; r_ofst <= 1; r_ofst++)
				{
					for (int c_ofst = -1; c_ofst <= 1; c_ofst++)
					{
						if ((r_ofst == c_ofst) && (r_ofst == 0))
						{
							continue;
						}

						else
						{
							n_bors += buffer_grid[(row + r_ofst + grid_h)%grid_h][(col + c_ofst + grid_w)%grid_w];
						}
					}
				}

				//applying the rules for Conway's game of life
				if (((buffer_grid[row][col] && ((n_bors == 2) || (n_bors == 3)))) || ((!buffer_grid[row][col]) && (n_bors == 3)))
				{
					grid[row][col] = 1;
					heatmap[row][col] += 1;
				}

				else
				{
					grid[row][col] = 0;
				}

			}
		}
			//writing a pbm image
			//https://en.wikipedia.org/wiki/Netpbm#PBM_example
			char name[10];
			snprintf(name, 10, "%05d.pbm", curr_gen);

			FILE* pbmimg;
			pbmimg = fopen(name, "wb");
			 
		    fprintf(pbmimg, "P1\n"); 
		  
		    fprintf(pbmimg, "%d %d\n", grid_w, grid_h); 
		  
		    fprintf(pbmimg, "1\n"); 
		    int count = 0;
		    for (int row = 0; row < grid_h; row++) {
		        for (int col = 0; col < grid_w; col++) {
		            fprintf(pbmimg, "%d ",grid[row][col]);
		        }
		        fprintf(pbmimg, "\n");
		    }
		    fclose(pbmimg);
		curr_gen += 1;
	}
	FILE* pgmimg;
	pgmimg = fopen("heatmap.pgm", "wb");
	 
    fprintf(pgmimg, "P2\n"); 
  
    fprintf(pgmimg, "%d %d\n", grid_w, grid_h); 
  
    fprintf(pgmimg, "255\n"); 
    int count = 0, norm;
    for (int row = 0; row < grid_h; row++) {
        for (int col = 0; col < grid_w; col++) {
			norm = (int) ((heatmap[row][col]/(((float) gens))*255.0));
			norm = 255 - norm;
            fprintf(pgmimg, "%d ", norm);
        }
        fprintf(pgmimg, "\n");
    }
    fclose(pgmimg);
}
