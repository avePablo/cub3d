/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idiaz-ca <idiaz-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 12:24:12 by idiaz-ca          #+#    #+#             */
/*   Updated: 2026/05/13 17:22:46 by idiaz-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/* Devuelve el índice donde empieza el mapa en el array `file` */
int	find_map_start(char **file)
{
	int	i;

	i = 0;
	while (file[i] && (is_config_line(file[i]) || is_empty_line(file[i])))
		i++;
	return (i);
}

/* Crea el array de configuración copiando las primeras `map_start` líneas */
static char	**alloc_config(char **file, int map_start)
{
	char	**config;
	int		j;

	config = malloc(sizeof(char *) * (map_start + 1));
	if (!config)
		return (NULL);
	j = 0;
	while (j < map_start)
	{
		config[j] = file[j];
		j++;
	}
	config[j] = NULL;
	return (config);
}

/* Crea el array del mapa (solo líneas no vacías) a partir de map_start */
static char	**alloc_map(char **file, int map_start)
{
	char	**map;
	int		k;
	int		j;
	int		m;

	k = 0;
	while (file[map_start + k])
		k++;
	map = malloc(sizeof(char *) * (k + 1));
	if (!map)
		return (NULL);
	j = 0;
	m = 0;
	while (j < k)
	{
		if (!is_empty_line(file[map_start + j]))
		{
			map[m] = file[map_start + j];
			m++;
		}
		j++;
	}
	map[m] = NULL;
	return (map);
}

/* Separa el archivo en configuración y mapa */
void	split_file(char **file, char ***config, char ***map)
{
	int	map_start;

	if (!file)
		return ;
	map_start = find_map_start(file);
	*config = alloc_config(file, map_start);
	if (!*config)
		return ;
	*map = alloc_map(file, map_start);
	if (!*map)
	{
		free(*config);
		*config = NULL;
		return ;
	}
}
