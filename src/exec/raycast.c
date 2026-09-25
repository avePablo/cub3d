/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfuto <kfuto@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/02 17:51:17 by kfuto             #+#    #+#             */
/*   Updated: 2026/05/07 16:13:28 by kfuto            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/* Advances cell by cell through the grid
	following the ray until it hits a wall */
void	perform_dda(t_game *g, t_raycast *r)
{
	int	hit;

	hit = 0;
	while (!hit)
	{
		if (r->side_x < r->side_y)
		{
			r->side_x += r->delta_x;
			r->map_x += r->step_x;
			r->side = 0;
		}
		else
		{
			r->side_y += r->delta_y;
			r->map_y += r->step_y;
			r->side = 1;
		}
		if (get_cell(g, r->map_x, r->map_y) == '1')
			hit = 1;
		if (r->map_x < 0 || r->map_y < 0)
			break ;
		if (!g->map[r->map_y])
			break ;
	}
}

/* Clears the image and casts one ray per
	screen column to render the frame */
void	raycast(t_game *g)
{
	t_raycast	r;
	int			x;

	ft_memset(g->img->pixels, 0, g->img->width * g->img->height * 4);
	x = 0;
	while (x < WINDOW_WIDTH)
	{
		init_ray(g, &r, x);
		init_dda(g, &r);
		perform_dda(g, &r);
		get_line_height(g, &r);
		draw_column(g, &r, x);
		x++;
	}
}
