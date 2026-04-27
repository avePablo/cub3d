#include "cub3D.h"

void	init_player_from_map(t_game *g)
{
	int	y;
	int	x;

	y = 0;
	while (g->map[y])
	{
		x = 0;
		while (g->map[y][x])
		{
			if (g->map[y][x] == 'N'
				|| g->map[y][x] == 'S'
				|| g->map[y][x] == 'E'
				|| g->map[y][x] == 'W')
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