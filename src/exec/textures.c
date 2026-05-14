/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idiaz-ca <idiaz-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/10 13:47:08 by idiaz-ca          #+#    #+#             */
/*   Updated: 2026/05/10 18:47:17 by idiaz-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/*Obtiene el píxel de una textura en las coordenadas dadas*/
uint32_t	get_texture_pixel(mlx_texture_t *tex, int x, int y)
{
	uint8_t	*p;

	p = &tex->pixels[(y * tex->width + x) * 4];
	return ((p[0] << 24) | (p[1] << 16) | (p[2] << 8) | p[3]);
}

/*carga las texturas*/
void	load_textures(t_game *game)
{
	game->tex_no = mlx_load_png(game->no);
	game->tex_so = mlx_load_png(game->so);
	game->tex_we = mlx_load_png(game->we);
	game->tex_ea = mlx_load_png(game->ea);
	if (!game->tex_no || !game->tex_so || !game->tex_we || !game->tex_ea)
	{
		ft_putstr_fd("Error loading textures\n", 2);
		exit(1);
	}
}
