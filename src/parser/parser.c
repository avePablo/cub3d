/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idiaz-ca <idiaz-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/09 12:23:44 by idiaz-ca          #+#    #+#             */
/*   Updated: 2026/04/09 12:23:46 by idiaz-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

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
