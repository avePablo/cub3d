/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idiaz-ca <idiaz-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 12:23:44 by idiaz-ca          #+#    #+#             */
/*   Updated: 2026/05/10 19:22:42 by idiaz-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// Comprueba que haya exactamente un jugador en el mapa
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

/* Valida un caracter del mapa y comprueba si la celda es cerrada */
static void	validate_map_cell(char **map, int y, int x)
{
	if (map[y][x] != '0' && map[y][x] != '1' && map[y][x] != 'N'
		&& map[y][x] != 'S' && map[y][x] != 'E' && map[y][x] != 'W'
		&& map[y][x] != ' ' && map[y][x] != '\n')
	{
		ft_putstr_fd("Error: Invalid map character\n", 2);
		exit(1);
	}
	if (map[y][x] == '0' || map[y][x] == 'N' || map[y][x] == 'S'
		|| map[y][x] == 'E' || map[y][x] == 'W')
	{
		if (!is_valid_cell(map, y + 1, x) || !is_valid_cell(map, y - 1, x)
			|| !is_valid_cell(map, y, x + 1) || !is_valid_cell(map, y, x - 1))
		{
			ft_putstr_fd("Error: Map not closed\n", 2);
			exit(1);
		}
	}
}

/* Valida que el mapa esté cerrado
(que no haya espacios alrededor de los '0' o jugadores) */
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
			validate_map_cell(map, y, x);
			x++;
		}
		y++;
	}
}

/* Agrega una línea al array de strings (file) y devuelve
 el nuevo array (libera el antiguo)*/
static char	**add_line(char **file, char *line, int size)
{
	char	**new;
	int		i;

	new = malloc(sizeof(char *) * (size + 2));
	if (!new)
	{
		free(file);
		return (NULL);
	}
	i = 0;
	while (i < size)
	{
		new[i] = file[i];
		i++;
	}
	new[i] = line;
	new[i + 1] = NULL;
	free(file);
	return (new);
}

// Lee el archivo línea por línea y lo guarda en un array de strings
char	**read_file(char *filename)
{
	int		fd;
	char	*line;
	char	**file;
	int		i;

	i = 0;
	file = NULL;
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (NULL);
	line = get_next_line(fd);
	while (line)
	{
		file = add_line(file, line, i);
		if (!file)
			return (NULL);
		i++;
		line = get_next_line(fd);
	}
	close(fd);
	return (file);
}
