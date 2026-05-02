/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfuto <kfuto@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 12:23:44 by idiaz-ca          #+#    #+#             */
/*   Updated: 2026/05/02 16:41:13 by kfuto            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	validate_player(char **map)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	count = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'N' || map[i][j] == 'S' || map[i][j] == 'E'
				|| map[i][j] == 'W')
				count++;
			j++;
		}
		i++;
	}
	if (count != 1)
	{
		ft_putstr_fd("Error: Invalid number of players\n", 2);
		exit(1);
	}
}

void	validate_map_closed(char **map)
{
	int	y;
	int	x;

	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == '0' || map[y][x] == 'N' || map[y][x] == 'S'
				|| map[y][x] == 'E' || map[y][x] == 'W')
			{
				if (!is_valid_cell(map, y + 1, x) || !is_valid_cell(map, y - 1,
						x) || !is_valid_cell(map, y, x + 1)
					|| !is_valid_cell(map, y, x - 1))
				{
					ft_putstr_fd("Error: Map not closed\n", 2);
					exit(1);
				}
			}
			x++;
		}
		y++;
	}
}

// Lee el archivo y devuelve un array de strings con su contenido
char	**read_file(char *filename)
{
	int		fd;
	char	*line;
	char	**file;
	int		i;
	int		count;

	i = 0;
	count = 0;
	// 1. Abrir archivo
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (NULL);
	// 2. Contar líneas
	while ((line = get_next_line(fd)))
	{
		count++;
		free(line);
	}
	close(fd);
	// 3. Reservar memoria
	file = malloc(sizeof(char *) * (count + 1));
	if (!file)
		return (NULL);
	// 4. Volver a abrir
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (NULL);
	// 5. Guardar líneas
	while ((line = get_next_line(fd)))
	{
		file[i++] = line;
	}
	file[i] = NULL;
	close(fd);
	return (file);
}
