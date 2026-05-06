/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idiaz-ca <idiaz-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/02 19:00:06 by kfuto             #+#    #+#             */
/*   Updated: 2026/05/06 09:49:35 by idiaz-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// Función auxiliar para determinar si una línea está vacía (solo espacios o nueva línea)
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
al	mapa(devuelve 1) o a la configuración (devuelve 0)*/
int	is_map_line(char *line)
{
	int	i;

	i = 0;
	if (!line || is_empty_line(line))
		return (0);
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

/* Funcion que devuelve 1 si la línea es una línea de configuración válida (NO,
	SO, WE, EA, F o C)*/
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

// Función auxiliar para validar que una celda del mapa es válida (dentro de los límites y no es un espacio)
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
