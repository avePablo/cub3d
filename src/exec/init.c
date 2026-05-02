#include "cub3D.h"

void	init_ray(t_game *g, int x, double *camera_x, double *ray_dir_x,
		double *ray_dir_y)
{
	*camera_x = 2 * x / (double)800 - 1;
	*ray_dir_x = g->player.dir_x + g->player.plane_x * (*camera_x);
	*ray_dir_y = g->player.dir_y + g->player.plane_y * (*camera_x);
	if (*ray_dir_x == 0)
		*ray_dir_x = 0.000001;
	if (*ray_dir_y == 0)
		*ray_dir_y = 0.000001;
}

void	init_dda(t_game *g, double ray_dir_x, double ray_dir_y, int *map_x,
		int *map_y, double *delta_x, double *delta_y, double *side_x,
		double *side_y, int *step_x, int *step_y)
{
	*map_x = (int)g->player.pos_x;
	*map_y = (int)g->player.pos_y;
	*delta_x = fabs(1 / ray_dir_x);
	*delta_y = fabs(1 / ray_dir_y);
	if (ray_dir_x < 0)
	{
		*step_x = -1;
		*side_x = (g->player.pos_x - *map_x) * (*delta_x);
	}
	else
	{
		*step_x = 1;
		*side_x = (*map_x + 1.0 - g->player.pos_x) * (*delta_x);
	}
	if (ray_dir_y < 0)
	{
		*step_y = -1;
		*side_y = (g->player.pos_y - *map_y) * (*delta_y);
	}
	else
	{
		*step_y = 1;
		*side_y = (*map_y + 1.0 - g->player.pos_y) * (*delta_y);
	}
}

void	init_player_from_map(t_game *g)
{
	int y;
	int x;

	y = 0;
	while (g->map[y])
	{
		x = 0;
		while (g->map[y][x])
		{
			if (g->map[y][x] == 'N' || g->map[y][x] == 'S'
				|| g->map[y][x] == 'E' || g->map[y][x] == 'W')
			{
				g->player.pos_x = x + 0.5;
				g->player.pos_y = y + 0.5;

				if (g->map[y][x] == 'N')
				{
					g->player.dir_x = 0;
					g->player.dir_y = -1;
					g->player.plane_x = 0.66;
					g->player.plane_y = 0;
				}
				if (g->map[y][x] == 'S')
				{
					g->player.dir_x = 0;
					g->player.dir_y = 1;
					g->player.plane_x = -0.66;
					g->player.plane_y = 0;
				}
				if (g->map[y][x] == 'E')
				{
					g->player.dir_x = 1;
					g->player.dir_y = 0;
					g->player.plane_x = 0;
					g->player.plane_y = 0.66;
				}
				if (g->map[y][x] == 'W')
				{
					g->player.dir_x = -1;
					g->player.dir_y = 0;
					g->player.plane_x = 0;
					g->player.plane_y = -0.66;
				}
				g->map[y][x] = '0';
				return ;
			}
			x++;
		}
		y++;
	}
}
