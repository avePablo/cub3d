/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfuto <kfuto@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/14 00:00:00 by idiaz-ca          #+#    #+#             */
/*   Updated: 2026/05/14 15:41:43 by kfuto            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	free_array(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
		free(arr[i++]);
	free(arr);
}

void	free_game(t_game *game)
{
	if (!game)
		return ;
	free_array(game->map);
	if (game->no)
		free(game->no);
	if (game->so)
		free(game->so);
	if (game->we)
		free(game->we);
	if (game->ea)
		free(game->ea);
	if (game->tex_no)
		mlx_delete_texture(game->tex_no);
	if (game->tex_so)
		mlx_delete_texture(game->tex_so);
	if (game->tex_we)
		mlx_delete_texture(game->tex_we);
	if (game->tex_ea)
		mlx_delete_texture(game->tex_ea);
}
