/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfuto <kfuto@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/02 18:55:04 by kfuto             #+#    #+#             */
/*   Updated: 2026/05/15 02:06:42 by kfuto            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/* Callback called every frame by MLX, triggers raycast rendering */
static void	render(void *param)
{
	t_game	*g;

	g = (t_game *)param;
	handle_input(g);
	raycast(g);
}

/* Entry point: initializes the game state, the map,
   the MLX window, and starts the main loop */
int	main(int argc, char **argv)
{
	t_game	game;

	ft_memset(&game, 0, sizeof(t_game));
	if (init_map(argc, argv, &game))
	{
		free_game(&game);
		return (1);
	}
	if (init_mlx(&game))
	{
		free_game(&game);
		return (1);
	}
	mlx_loop_hook(game.mlx, render, &game);
	mlx_loop(game.mlx);
	mlx_terminate(game.mlx);
	free_game(&game);
	return (0);
}
