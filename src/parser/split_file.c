/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idiaz-ca <idiaz-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 12:24:12 by idiaz-ca          #+#    #+#             */
/*   Updated: 2026/05/06 10:36:47 by idiaz-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// Separa el archivo en configuración y mapa
void	split_file(char **file, char ***config, char ***map)
{
	int	i;
	int	j;
	int	k;
	int	map_start;
	int	m;

	i = 0;
	// 1. Saltar config + líneas vacías
	while (file[i] && (is_config_line(file[i]) || is_empty_line(file[i])))
		i++;
	map_start = i;
	// 2. CONFIG
	*config = malloc(sizeof(char *) * (map_start + 1));
	if (!*config)
		return ;
	j = 0;
	while (j < map_start)
	{
		(*config)[j] = file[j];
		j++;
	}
	(*config)[j] = NULL;
	// 3. MAP (solo líneas válidas)
	k = 0;
	while (file[map_start + k])
		k++;
	*map = malloc(sizeof(char *) * (k + 1));
	if (!*map)
	{
		free(*config);
		return ;
	}
	j = 0;
	m = 0;
	while (j < k)
	{
		if (!is_empty_line(file[map_start + j]))
		{
			(*map)[m] = file[map_start + j];
			m++;
		}
		j++;
	}
	(*map)[m] = NULL;
}
