/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfuto <kfuto@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/02 18:55:04 by kfuto             #+#    #+#             */
/*   Updated: 2026/05/02 19:08:25 by kfuto            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/* Callback llamado cada frame por MLX, lanza el renderizado por raycast */
static void	render(void *param)
{
	t_game	*g;

	g = (t_game *)param;
	raycast(g);
}

/* Punto de entrada: inicializa el estado del juego, el mapa,
   la ventana MLX y arranca el bucle principal */
int	main(int argc, char **argv)
{
	t_game	game;

	ft_memset(&game, 0, sizeof(t_game));
	if (init_map(argc, argv, &game))
		return (1);
	if (init_mlx(&game))
		return (1);
	mlx_loop_hook(game.mlx, render, &game);
	mlx_loop(game.mlx);
	mlx_terminate(game.mlx);
	return (0);
}
