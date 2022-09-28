//my implementation of game of life in c
#include <stdio.h>

int main()
{
	int grid_w = 7;
	int grid_h = 7;
	int grid[grid_h][grid_w];
	int buffer_grid[grid_h][grid_w];

	int gens = 100;
	
//setting the entire grid and buffer grid to dead cells
	for (int row = 0; row < grid_h; row++)
	{
		for (int col = 0; col < grid_w; col++)
		{
			grid[row][col] = 0;
			buffer_grid[row][col] = 0;
		}
	}

//making the blinker pattern
	grid[3][2] = 1;
	grid[3][3] = 1;
	grid[3][4] = 1;
	buffer_grid[3][2] = 1;
	buffer_grid[3][3] = 1;
	buffer_grid[3][4] = 1;

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

		//printing the buffer grid [this is currently there only for debugging,
		//eventually i'll be either using sdl or writing images 
		//and then animating them using ffmpeg]
		for (int row = 0; row < grid_h; row++)
		{
			for (int col = 0; col < grid_w; col++)
			{
				printf("%d ", buffer_grid[row][col]);
			}
			printf("\n");
		}
		printf("\n");

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
				if ((buffer_grid[row][col] && (1 < n_bors < 4)) || ((!buffer_grid[row][col]) && (n_bors == 3)))
				{
					grid[row][col] = 1;
				}

				else
				{
					grid[row][col] = 0;
				}

			}
		}
		curr_gen += 1;
	}
}
