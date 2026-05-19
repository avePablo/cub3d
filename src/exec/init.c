/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfuto <kfuto@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/02 18:57:32 by kfuto             #+#    #+#             */
/*   Updated: 2026/05/15 01:38:25 by kfuto            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/* Validates the argument count, file extension, and reads the file content */
static int	validate_and_read_file(int argc, char **argv, char ***file)
{
	if (argc != 2)
		return (ft_putstr_fd("Error\n", 2), 1);
	if (!check_extension(argv[1]))
	{
		ft_putstr_fd("Error: Invalid file extension\n", 2);
		return (1);
	}
	*file = read_file(argv[1]);
	if (!*file)
		return (ft_putstr_fd("Error\n", 2), 1);
	return (0);
}

// Validates the map lines
static void	validate_map_lines(char **file)
{
	int	map_start;

	map_start = find_map_start(file);
	while (file[map_start])
	{
		if (is_empty_line(file[map_start]))
		{
			ft_putstr_fd("Error: Empty line detected within the map\n", 2);
			exit(1);
		}
		map_start++;
	}
}

/* Reads the map file, splits it into config and map,
   validates the map, and initializes the player position */
int	init_map(int argc, char **argv, t_game *game)
{
	char	**file;
	char	**config;
	char	**old_map;

	if (validate_and_read_file(argc, argv, &file))
		return (1);
	validate_map_lines(file);
	split_file(file, &config, &game->map);
	old_map = game->map;
	game->map = make_map_rectangular(game->map);
	free(old_map);
	parse_config(config, game);
	free(config);
	free_array(file);
	load_textures(game);
	validate_textures(game);
	validate_player(game->map);
	validate_map_closed(game->map);
	init_player_from_map(game);
	validate_map(game);
	return (0);
}

/* Initializes the MLX window, creates the image buffer,
	and attaches it to the window */
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
