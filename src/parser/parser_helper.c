/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_helper.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idiaz-ca <idiaz-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/02 19:00:06 by kfuto             #+#    #+#             */
/*   Updated: 2026/05/11 10:39:45 by idiaz-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/* Helper to determine whether a line is empty
	(spaces only or newline only) */
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

/* Helper to determine whether a line belongs
	to the map (returns 1) or the configuration (returns 0) */
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

/* Returns 1 if the line is a valid configuration line
	(NO, SO, WE, EA, F or C) */
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

/* Helper to validate that a map cell is valid */
int	is_valid_cell(char **map, int y, int x)
{
	if (y < 0 || x < 0)
		return (0);
	if (!map[y])
		return (0);
	if (x >= (int)ft_strlen(map[y]))
		return (0);
	if (map[y][x] == '\n' || map[y][x] == '\0')
		return (0);
	return (1);
}
