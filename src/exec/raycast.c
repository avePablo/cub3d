#include "cub3D.h"

static void	init_ray(t_game *g, int x, double *camera_x,
					double *ray_dir_x, double *ray_dir_y)
{
	*camera_x = 2 * x / (double)800 - 1;
	*ray_dir_x = g->player.dir_x + g->player.plane_x * (*camera_x);
	*ray_dir_y = g->player.dir_y + g->player.plane_y * (*camera_x);

	if (*ray_dir_x == 0)
		*ray_dir_x = 0.000001;
	if (*ray_dir_y == 0)
		*ray_dir_y = 0.000001;
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

static void	init_dda(t_game *g, double ray_dir_x, double ray_dir_y,
				int *map_x, int *map_y,
				double *delta_x, double *delta_y,
				double *side_x, double *side_y,
				int *step_x, int *step_y)
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

void	draw_column(t_game *g, int x, int start, int end, int side)
{
	(void)g;
	(void)x;
	(void)start;
	(void)end;
	(void)side;
}

void	raycast(t_game *g)
{
	int		x;
	double	camera_x;
	double	ray_dir_x;
	double	ray_dir_y;

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

// void raycast(t_game *g)
// {
// 	int x = 0;

// 	while (x < 800)
// 	{
// 		double camera_x = 2 * x / (double)800 - 1;

// 		double ray_dir_x = g->player.dir_x + g->player.plane_x * camera_x;
// 		double ray_dir_y = g->player.dir_y + g->player.plane_y * camera_x;

// 		int map_x = (int)g->player.pos_x;
// 		int map_y = (int)g->player.pos_y;

// 		double delta_dist_x = fabs(1 / ray_dir_x);
// 		double delta_dist_y = fabs(1 / ray_dir_y);

// 		double side_dist_x;
// 		double side_dist_y;

// 		int step_x;
// 		int step_y;

// 		int hit = 0;
// 		int side;

//     		if (ray_dir_x < 0)
// 		{
// 			step_x = -1;
// 			side_dist_x = (g->player.pos_x - map_x) * delta_dist_x;
// 		}
// 		else
// 		{
// 			step_x = 1;
// 			side_dist_x = (map_x + 1.0 - g->player.pos_x) * delta_dist_x;
// 		}

// 		if (ray_dir_y < 0)
// 		{
// 			step_y = -1;
// 			side_dist_y = (g->player.pos_y - map_y) * delta_dist_y;
// 		}
// 		else
// 		{
// 			step_y = 1;
// 			side_dist_y = (map_y + 1.0 - g->player.pos_y) * delta_dist_y;
// 		}

// 		while (hit == 0)
// 		{
// 			if (side_dist_x < side_dist_y)
// 			{
// 				side_dist_x += delta_dist_x;
// 				map_x += step_x;
// 				side = 0;
// 			}
// 			else
// 			{
// 				side_dist_y += delta_dist_y;
// 				map_y += step_y;
// 				side = 1;
// 			}

// 			if (g->map[map_y][map_x] == '1')
// 				hit = 1;
// 		}
//         		double perp_wall_dist;

// 		if (side == 0)
// 			perp_wall_dist = (map_x - g->player.pos_x + (1 - step_x) / 2) / ray_dir_x;
// 		else
// 			perp_wall_dist = (map_y - g->player.pos_y + (1 - step_y) / 2) / ray_dir_y;
//         		int line_height = (int)(600 / perp_wall_dist);

//         		int start = -line_height / 2 + 300;
// 		int end = line_height / 2 + 300;

// 		draw_column(g, x, start, end, side);

// 		x++;
// 	}
// }