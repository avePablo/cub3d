/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rectangular.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idiaz-ca <idiaz-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/11 11:00:05 by idiaz-ca          #+#    #+#             */
/*   Updated: 2026/05/11 11:00:06 by idiaz-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	get_max_width(char **map)
{
	int	i;
	int	max;
	int	len;

	i = 0;
	max = 0;
	while (map[i])
	{
		len = ft_strlen(map[i]);
		if (map[i][len - 1] == '\n')
			len--;
		if (len > max)
			max = len;
		i++;
	}
	return (max);
}

static void	fill_row(char *dst, char *src, int width)
{
	int	j;

	j = 0;
	while (j < width)
	{
		if (j < (int)ft_strlen(src) && src[j] != '\n')
			dst[j] = src[j];
		else
			dst[j] = ' ';
		j++;
	}
	dst[j] = '\0';
}

char	**make_map_rectangular(char **map)
{
	char	**new_map;
	int		height;
	int		width;
	int		i;

	height = 0;
	while (map[height])
		height++;
	width = get_max_width(map);
	new_map = malloc(sizeof(char *) * (height + 1));
	if (!new_map)
		return (NULL);
	i = 0;
	while (i < height)
	{
		new_map[i] = malloc(width + 1);
		if (!new_map[i])
			return (NULL);
		fill_row(new_map[i], map[i], width);
		i++;
	}
	new_map[i] = NULL;
	return (new_map);
}
