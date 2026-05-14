/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_texture.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idiaz-ca <idiaz-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/14 16:58:07 by idiaz-ca          #+#    #+#             */
/*   Updated: 2026/05/14 17:00:42 by idiaz-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// Comprueba si line empieza con prefix
int	starts_with(char *line, char *prefix)
{
	int	len;

	len = 0;
	while (prefix[len] && line[len] == prefix[len])
		len++;
	return (prefix[len] == '\0');
}

/* Extrae ruta: "NO ./a.png"
	-> "./a.png" (debemos evitar copiar espacios y saltos de línea)*/
static char	*extract_path(char *line)
{
	char	*start;
	char	*end;
	char	*res;

	while (*line && *line != ' ')
		line++;
	while (*line == ' ')
		line++;
	start = line;
	end = line;
	while (*end && *end != '\n')
		end++;
	res = malloc(end - start + 1);
	if (!res)
		return (NULL);
	ft_strlcpy(res, start, end - start + 1);
	return (res);
}

void	parse_texture(char *line, char **texture, char *id)
{
	if (*texture)
	{
		printf("Error: duplicate %s\n", id);
		exit(1);
	}
	*texture = extract_path(line);
	if (!*texture)
	{
		printf("Error: malloc failed\n");
		exit(1);
	}
}
