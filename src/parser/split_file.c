/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idiaz-ca <idiaz-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 12:24:12 by idiaz-ca          #+#    #+#             */
/*   Updated: 2026/04/09 13:47:44 by idiaz-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// Función auxiliar para determinar si una línea pertenece al mapa(devuelve 1) o a la configuración (devuelve 0)
static int is_map_line(char *line)
{
    int i = 0;

    if (!line || line[0] == '\n')
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
void	split_file(char **file, char ***config, char ***map)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	// 1. Contar líneas de configuración
	while (file[i] && !is_map_line(file[i]))
		i++;
	*config = malloc(sizeof(char *) * (i + 1));
	// 2. Guardar líneas de configuración
	for (j = 0; j < i; j++)
		(*config)[j] = file[j];
	(*config)[j] = NULL;
	k = 0;
	// 3. Contar líneas de mapa
	while (file[i + k])
		k++;
	*map = malloc(sizeof(char *) * (k + 1));
	// 4. Guardar líneas de mapa
	for (j = 0; j < k; j++)
		(*map)[j] = file[i + j];
	(*map)[j] = NULL;
}
