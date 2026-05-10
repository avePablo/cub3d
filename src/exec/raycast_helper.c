/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_helper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idiaz-ca <idiaz-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/02 17:51:13 by kfuto             #+#    #+#             */
/*   Updated: 2026/05/10 14:54:09 by idiaz-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/* Calcula la distancia perpendicular a la pared
y el rango vertical a dibujar */
void	get_line_height(t_game *g, t_raycast *r)
{
	if (r->side == 0)
		r->perp_wall_dist = (r->map_x - g->player.pos_x + (1 - r->step_x) / 2)
			/ r->ray_dir_x;
	else
		r->perp_wall_dist = (r->map_y - g->player.pos_y + (1 - r->step_y) / 2)
			/ r->ray_dir_y;
	r->line_height = (int)(WINDOW_HEIGHT / r->perp_wall_dist);
	r->draw_start = -r->line_height / 2 + WINDOW_HEIGHT / 2;
	r->draw_end = r->line_height / 2 + WINDOW_HEIGHT / 2;
}

/* Devuelve el caracter del mapa en (x, y),
tratando fuera de limites como pared */
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
