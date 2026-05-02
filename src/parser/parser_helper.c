/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfuto <kfuto@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/02 19:00:06 by kfuto             #+#    #+#             */
/*   Updated: 2026/05/02 19:00:07 by kfuto            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	is_empty_line(char *line)
{
	int	i;

	i = 0;
	if (!line)
		return (1);
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '\n')
			return (0);
		i++;
	}
	return (1);
}

/* Función auxiliar para determinar si una línea pertenece 
al mapa(devuelve 1) o a la configuración (devuelve 0)*/
int	is_map_line(char *line)
{
	int	i;

	i = 0;
	while (line[i] == ' ')
		i++;
	if (line[i] != '1' && line[i] != '0' && line[i] != 'N' && line[i] != 'S'
		&& line[i] != 'E' && line[i] != 'W')
		return (0);
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '1' && line[i] != '0' && line[i] != 'N'
			&& line[i] != 'S' && line[i] != 'E' && line[i] != 'W'
			&& line[i] != '\n')
			return (0);
		i++;
	}
	return (1);
}

int	is_config_line(char *line)
{
	int	i;

	i = 0;
	while (line[i] == ' ')
		i++;
	return (ft_strncmp(&line[i], "NO ", 3) == 0 || ft_strncmp(&line[i], "SO ",
			3) == 0 || ft_strncmp(&line[i], "WE ", 3) == 0
		|| ft_strncmp(&line[i], "EA ", 3) == 0 || ft_strncmp(&line[i], "F ",
			2) == 0 || ft_strncmp(&line[i], "C ", 2) == 0);
}

int	is_valid_cell(char **map, int y, int x)
{
	if (y < 0 || x < 0)
		return (0);
	if (!map[y] || x >= (int)ft_strlen(map[y]))
		return (0);
	if (map[y][x] == ' ')
		return (0);
	return (1);
}
