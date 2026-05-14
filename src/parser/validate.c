/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idiaz-ca <idiaz-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/10 19:11:45 by idiaz-ca          #+#    #+#             */
/*   Updated: 2026/05/13 17:45:19 by idiaz-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	check_extension(char *filename)
{
	int	len;

	len = ft_strlen(filename);
	if (len < 5)
		return (0);
	if (ft_strncmp(filename + len - 4, ".cub", 4) != 0)
		return (0);
	return (1);
}

static void	check_texture(char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		ft_putstr_fd("Error: Invalid texture path\n", 2);
		exit(1);
	}
	close(fd);
}

static void	validate_map_borders(char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == '0')
			{
				if (i == 0 || j == 0 || !map[i + 1] || !map[i][j + 1] || map[i
					- 1][j] == ' ' || map[i + 1][j] == ' ' || map[i][j
					- 1] == ' ' || map[i][j + 1] == ' ')
				{
					ft_putstr_fd("Error: Map is not enclosed by walls\n", 2);
					exit(1);
				}
			}
			j++;
		}
		i++;
	}
}

void	validate_textures(t_game *game)
{
	check_texture(game->no);
	check_texture(game->so);
	check_texture(game->we);
	check_texture(game->ea);
}

void	validate_map(t_game *game)
{
	validate_map_borders(game->map);
}
