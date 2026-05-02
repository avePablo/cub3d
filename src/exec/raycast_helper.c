#include "cub3D.h"

int	get_line_height(t_game *g, int map_x, int map_y, double ray_dir_x,
		double ray_dir_y, int step_x, int step_y, int side,
		double *perp_wall_dist)
{
	if (side == 0)
		*perp_wall_dist = (map_x - g->player.pos_x + (1 - step_x) / 2)
			/ ray_dir_x;
	else
		*perp_wall_dist = (map_y - g->player.pos_y + (1 - step_y) / 2)
			/ ray_dir_y;
	return ((int)(600 / (*perp_wall_dist)));
}

void	put_pixel(mlx_image_t *img, int x, int y, uint32_t color)
{
	uint8_t	*pixel;

	if (x < 0 || y < 0 || x >= (int)img->width || y >= (int)img->height)
		return ;
	pixel = img->pixels + (y * img->width + x) * 4;
	pixel[0] = (color >> 24) & 0xFF;
	pixel[1] = (color >> 16) & 0xFF;
	pixel[2] = (color >> 8) & 0xFF;
	pixel[3] = (color >> 0) & 0xFF;
}

void	draw_column(t_game *g, int x, int start, int end, int side)
{
	int	wall_color;
	int	y;

	wall_color = side == 1 ? 0xAAAAAFF : 0xFFFFFFF;
	// Techo
	y = 0;
	while (y < start)
		put_pixel(g->img, x, y++, 0xDDDDDDFF);
	// Pared
	y = start < 0 ? 0 : start;
	while (y < end && y < 600)
		put_pixel(g->img, x, y++, wall_color);
	// Suelo
	while (y < 600)
		put_pixel(g->img, x, y++, 0x000000EE);
}

char	get_cell(t_game *g, int x, int y)
{
	if (!g->map[y])
		return ('1');
	if (x < 0 || y < 0)
		return ('1');
	if (x >= (int)ft_strlen(g->map[y]))
		return ('1');
	return (g->map[y][x]);
}
