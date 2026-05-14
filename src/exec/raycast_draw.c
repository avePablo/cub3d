/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_draw.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idiaz-ca <idiaz-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/10 14:55:23 by idiaz-ca          #+#    #+#             */
/*   Updated: 2026/05/10 18:23:47 by idiaz-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

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

/* Obtiene la textura correspondiente a un rayo */
static mlx_texture_t	*get_texture(t_game *g, t_raycast *r)
{
	if (r->side == 0)
	{
		if (r->ray_dir_x > 0)
			return (g->tex_we);
		return (g->tex_ea);
	}
	if (r->ray_dir_y > 0)
		return (g->tex_no);
	return (g->tex_so);
}

/* Obtiene la coordenada X de la textura para un rayo */
static int	get_tex_x(t_game *g, t_raycast *r, mlx_texture_t *tex)
{
	double	wall_x;

	if (r->side == 0)
		wall_x = g->player.pos_y + r->perp_wall_dist * r->ray_dir_y;
	else
		wall_x = g->player.pos_x + r->perp_wall_dist * r->ray_dir_x;
	wall_x -= floor(wall_x);
	return ((int)(wall_x * tex->width));
}

/* Dibuja la pared para una columna de pantalla */
static void	draw_wall(t_game *g, t_raycast *r, mlx_texture_t *tex, int x)
{
	int			tex_x;
	int			tex_y;
	uint32_t	color;
	int			y;

	tex_x = get_tex_x(g, r, tex);
	y = r->draw_start;
	if (y < 0)
		y = 0;
	while (y < r->draw_end && y < WINDOW_HEIGHT)
	{
		tex_y = (y - r->draw_start) * tex->height / r->line_height;
		color = get_texture_pixel(tex, tex_x, tex_y);
		put_pixel(g->img, x, y, color);
		y++;
	}
}

/*dibuja el techo,
	el fragmento de pared y el suelo para una columna de pantalla*/
void	draw_column(t_game *g, t_raycast *r, int x)
{
	mlx_texture_t	*tex;
	int				y;

	tex = get_texture(g, r);
	y = 0;
	while (y < r->draw_start)
		put_pixel(g->img, x, y++, g->ceiling_color);
	draw_wall(g, r, tex, x);
	y = r->draw_end;
	if (y < 0)
		y = 0;
	while (y < WINDOW_HEIGHT)
		put_pixel(g->img, x, y++, g->floor_color);
}
