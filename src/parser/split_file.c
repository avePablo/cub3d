/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfuto <kfuto@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 12:24:12 by idiaz-ca          #+#    #+#             */
/*   Updated: 2026/04/27 16:42:26 by kfuto            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int is_empty_line(char *line)
{
    int i = 0;

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

// Función auxiliar para determinar si una línea pertenece al mapa(devuelve 1) o a la configuración (devuelve 0)
int is_map_line(char *line)
{
    int i = 0;

    while (line[i] == ' ')
        i++;

    if (line[i] != '1' && line[i] != '0' &&
        line[i] != 'N' && line[i] != 'S' &&
        line[i] != 'E' && line[i] != 'W')
        return (0);

    while (line[i])
    {
        if (line[i] != ' ' &&
            line[i] != '1' &&
            line[i] != '0' &&
            line[i] != 'N' &&
            line[i] != 'S' &&
            line[i] != 'E' &&
            line[i] != 'W' &&
            line[i] != '\n')
            return (0);
        i++;
    }
    return (1);
}
// Separa el archivo en configuración y mapa
void split_file(char **file, char ***config, char ***map)
{
    int i = 0;
    int j;
    int k;
    int map_start;

    // 1. Saltar config + líneas vacías
    while (file[i] && (is_config_line(file[i]) || is_empty_line(file[i])))
        i++;

    map_start = i;

    // 2. CONFIG
    *config = malloc(sizeof(char *) * (map_start + 1));
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
        return;

    j = 0;
    int m = 0;

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

int is_config_line(char *line)
{
    int i = 0;

    while (line[i] == ' ')
        i++;

    return (
        ft_strncmp(&line[i], "NO ", 3) == 0 ||
        ft_strncmp(&line[i], "SO ", 3) == 0 ||
        ft_strncmp(&line[i], "WE ", 3) == 0 ||
        ft_strncmp(&line[i], "EA ", 3) == 0 ||
        ft_strncmp(&line[i], "F ", 2) == 0 ||
        ft_strncmp(&line[i], "C ", 2) == 0
    );
}

void	validate_player(char **map)
{
	int	i = 0;
	int	j;
	int	count = 0;

	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'N' || map[i][j] == 'S' ||
				map[i][j] == 'E' || map[i][j] == 'W')
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

static int	is_valid_cell(char **map, int y, int x)
{
	if (y < 0 || x < 0)
		return (0);
	if (!map[y] || x >= (int)ft_strlen(map[y]))
		return (0);
	if (map[y][x] == ' ')
		return (0);
	return (1);
}

void	validate_map_closed(char **map)
{
	int	y = 0;
	int	x;

	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (map[y][x] == '0' ||
				map[y][x] == 'N' ||
				map[y][x] == 'S' ||
				map[y][x] == 'E' ||
				map[y][x] == 'W')
			{
				if (!is_valid_cell(map, y + 1, x) ||
					!is_valid_cell(map, y - 1, x) ||
					!is_valid_cell(map, y, x + 1) ||
					!is_valid_cell(map, y, x - 1))
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