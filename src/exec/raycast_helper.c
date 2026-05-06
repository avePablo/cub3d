/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_helper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfuto <kfuto@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/02 17:51:13 by kfuto             #+#    #+#             */
/*   Updated: 2026/05/02 19:09:12 by kfuto            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/* Calcula la distancia perpendicular a la pared 
y el rango vertical a dibujar */
void	get_line_height(t_game *g, t_raycast *r)
{
	if (r->side == 0)
		r->perp_wall_dist = (r->map_x - g->player.pos_x
				+ (1 - r->step_x) / 2) / r->ray_dir_x;
	else
		r->perp_wall_dist = (r->map_y - g->player.pos_y
				+ (1 - r->step_y) / 2) / r->ray_dir_y;
	r->line_height = (int)(600 / r->perp_wall_dist);
	r->draw_start = -r->line_height / 2 + 300;
	r->draw_end = r->line_height / 2 + 300;
}

/* Escribe un pixel RGBA en el buffer de imagen en la posicion (x, y) */
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

/* Dibuja el techo, el fragmento de pared
 y el suelo para una columna de pantalla */
void	draw_column(t_game *g, t_raycast *r, int x)
{
	int	wall_color;
	int	y;

	if (r->side == 1)
		wall_color = 0xAAAAAAFF;
	else
		wall_color = 0xFFFFFFFF;
	y = 0;
	while (y < r->draw_start)
		put_pixel(g->img, x, y++, 0xDDDDDDFF);
	y = r->draw_start;
	if (y < 0)
		y = 0;
	while (y < r->draw_end && y < 600)
		put_pixel(g->img, x, y++, wall_color);
	while (y < 600)
		put_pixel(g->img, x, y++, 0x000000EE);
}
