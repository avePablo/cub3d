/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idiaz-ca <idiaz-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/02 18:57:32 by kfuto             #+#    #+#             */
/*   Updated: 2026/05/10 13:49:35 by idiaz-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/* Lee el fichero del mapa, lo divide en config y mapa,
   valida el mapa e inicializa la posicion del jugador */
int	init_map(int argc, char **argv, t_game *game)
{
	char	**file;
	char	**config;

	if (argc != 2)
		return (ft_putstr_fd("Error\n", 2), 1);
	if (!check_extension(argv[1]))
	{
		ft_putstr_fd("Error: Invalid file extension\n", 2);
		return (1);
	}
	file = read_file(argv[1]);
	if (!file)
		return (ft_putstr_fd("Error\n", 2), 1);
	split_file(file, &config, &game->map);
	parse_config(config, game);
	load_textures(game);
	validate_textures(game);
	validate_player(game->map);
	validate_map_closed(game->map);
	init_player_from_map(game);
	return (0);
}

/* Inicializa la ventana MLX, crea el buffer de imagen
   y lo asocia a la ventana */
int	init_mlx(t_game *game)
{
	game->mlx = mlx_init(WINDOW_WIDTH, WINDOW_HEIGHT, "Cub3D", true);
	if (!game->mlx)
		return (ft_putstr_fd("Error MLX\n", 2), 1);
	game->img = mlx_new_image(game->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!game->img)
		return (ft_putstr_fd("Error imagen\n", 2), 1);
	if (mlx_image_to_window(game->mlx, game->img, 0, 0) < 0)
		return (ft_putstr_fd("Error window\n", 2), 1);
	return (0);
}
