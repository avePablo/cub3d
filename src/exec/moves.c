/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idiaz-ca <idiaz-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/08 01:52:56 by kfuto             #+#    #+#             */
/*   Updated: 2026/05/13 18:33:29 by idiaz-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

#define MOVE_SPEED 0.10
#define ROT_SPEED 0.10

/* Rotates the direction and camera plane with a 2D rotation matrix.
	angle > 0 -> turns right, angle < 0 -> turns left */
static void	rotate_player(t_game *g, double angle)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = g->player.dir_x;
	g->player.dir_x = g->player.dir_x * cos(angle) - g->player.dir_y
		* sin(angle);
	g->player.dir_y = old_dir_x * sin(angle) + g->player.dir_y * cos(angle);
	old_plane_x = g->player.plane_x;
	g->player.plane_x = g->player.plane_x * cos(angle) - g->player.plane_y
		* sin(angle);
	g->player.plane_y = old_plane_x * sin(angle) + g->player.plane_y
		* cos(angle);
}

/* Tries to move the player in the (dx, dy) direction.
	Checks wall collisions before updating the position. */
static void	try_move(t_game *g, double dx, double dy)
{
	double	new_x;
	double	new_y;

	new_x = g->player.pos_x + dx;
	new_y = g->player.pos_y + dy;
	if (get_cell(g, (int)new_x, (int)g->player.pos_y) != '1')
		g->player.pos_x = new_x;
	if (get_cell(g, (int)g->player.pos_x, (int)new_y) != '1')
		g->player.pos_y = new_y;
}

/* Reads the keyboard state every frame and handles rotation / WASD / ESC */
void	handle_input(t_game *g)
{
	if (mlx_is_key_down(g->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(g->mlx);
	if (mlx_is_key_down(g->mlx, MLX_KEY_W))
		try_move(g, g->player.dir_x * MOVE_SPEED, g->player.dir_y * MOVE_SPEED);
	if (mlx_is_key_down(g->mlx, MLX_KEY_S))
		try_move(g, -g->player.dir_x * MOVE_SPEED, -g->player.dir_y
			* MOVE_SPEED);
	if (mlx_is_key_down(g->mlx, MLX_KEY_A))
		try_move(g, g->player.dir_y * MOVE_SPEED, -g->player.dir_x
			* MOVE_SPEED);
	if (mlx_is_key_down(g->mlx, MLX_KEY_D))
		try_move(g, -g->player.dir_y * MOVE_SPEED, g->player.dir_x
			* MOVE_SPEED);
	if (mlx_is_key_down(g->mlx, MLX_KEY_LEFT))
		rotate_player(g, -ROT_SPEED);
	if (mlx_is_key_down(g->mlx, MLX_KEY_RIGHT))
		rotate_player(g, ROT_SPEED);
}
