#include "cub3D.h"

static void put_pixel(mlx_image_t *img, int x, int y, uint32_t color)
{
    if (x < 0 || y < 0 || x >= (int)img->width || y >= (int)img->height)
        return ;
    uint8_t *pixel = img->pixels + (y * img->width + x) * 4;
    pixel[0] = (color >> 24) & 0xFF; // R
    pixel[1] = (color >> 16) & 0xFF; // G
    pixel[2] = (color >>  8) & 0xFF; // B
    pixel[3] = (color >>  0) & 0xFF; // A
}

void draw_column(t_game *g, int x, int start, int end, int side)
{
    int wall_color = side == 1 ? 0xAAAAAFF : 0xFFFFFFF;
    int y;

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

static char	get_cell(t_game *g, int x, int y)
{
	if (!g->map[y])
		return ('1');
	if (x < 0 || y < 0)
		return ('1');
	if (x >= (int)ft_strlen(g->map[y]))
		return ('1');
	return (g->map[y][x]);
}

static int	perform_dda(t_game *g, int *map_x, int *map_y,
					double *side_x, double *side_y,
					double delta_x, double delta_y,
					int step_x, int step_y)
{
	int	hit;
	int	side;

	hit = 0;

	while (!hit)
	{
		if (*side_x < *side_y)
		{
			*side_x += delta_x;
			*map_x += step_x;
			side = 0;
		}
		else
		{
			*side_y += delta_y;
			*map_y += step_y;
			side = 1;
		}
		if (get_cell(g, *map_x, *map_y) == '1')
			hit = 1;
		if (*map_x < 0 || *map_y < 0)
			break ;
		if (!g->map[*map_y])
			break ;
	}
	return (side);
}

static int	get_line_height(t_game *g, int map_x, int map_y,
					double ray_dir_x, double ray_dir_y,
					int step_x, int step_y, int side,
					double *perp_wall_dist)
{
	if (side == 0)
		*perp_wall_dist = (map_x - g->player.pos_x
			+ (1 - step_x) / 2) / ray_dir_x;
	else
		*perp_wall_dist = (map_y - g->player.pos_y
			+ (1 - step_y) / 2) / ray_dir_y;

	return ((int)(600 / (*perp_wall_dist)));
}

void	raycast(t_game *g)
{
	int		x;
	double	camera_x;
	double	ray_dir_x;
	double	ray_dir_y;

	ft_memset(g->img->pixels, 0, g->img->width * g->img->height * 4);
	x = 0;
	while (x < 800)
	{
		int	map_x;
		int	map_y;
		double	delta_x;
		double	delta_y;
		double	side_x;
		double	side_y;
		int	step_x;
		int	step_y;
		int	side;
		double	perp_wall_dist;
		int	line_height;

		init_ray(g, x, &camera_x, &ray_dir_x, &ray_dir_y);
		init_dda(g, ray_dir_x, ray_dir_y, &map_x, &map_y,
			&delta_x, &delta_y, &side_x, &side_y,
			&step_x, &step_y);

		side = perform_dda(g, &map_x, &map_y,
			&side_x, &side_y,
			delta_x, delta_y,
			step_x, step_y);

		line_height = get_line_height(g, map_x, map_y,
			ray_dir_x, ray_dir_y,
			step_x, step_y, side,
			&perp_wall_dist);

		draw_column(g, x,
			-line_height / 2 + 300,
			line_height / 2 + 300,
			side);

		x++;
	}
}
