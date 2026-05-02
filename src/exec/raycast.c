#include "cub3D.h"

static int	perform_dda(t_game *g, int *map_x, int *map_y, double *side_x,
		double *side_y, double delta_x, double delta_y, int step_x, int step_y)
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

void	raycast(t_game *g)
{
	int		x;
	double	camera_x;
	double	ray_dir_x;
	double	ray_dir_y;
	int		map_x;
	int		map_y;
	double	delta_x;
	double	delta_y;
	double	side_x;
	double	side_y;
	int		step_x;
	int		step_y;
	int		side;
	double	perp_wall_dist;
	int		line_height;

	ft_memset(g->img->pixels, 0, g->img->width * g->img->height * 4);
	x = 0;
	while (x < 800)
	{
		init_ray(g, x, &camera_x, &ray_dir_x, &ray_dir_y);
		init_dda(g, ray_dir_x, ray_dir_y, &map_x, &map_y, &delta_x, &delta_y,
			&side_x, &side_y, &step_x, &step_y);
		side = perform_dda(g, &map_x, &map_y, &side_x, &side_y, delta_x,
				delta_y, step_x, step_y);
		line_height = get_line_height(g, map_x, map_y, ray_dir_x, ray_dir_y,
				step_x, step_y, side, &perp_wall_dist);
		draw_column(g, x, -line_height / 2 + 300, line_height / 2 + 300, side);
		x++;
	}
}
