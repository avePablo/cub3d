/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_setter.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idiaz-ca <idiaz-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/02 19:00:14 by kfuto             #+#    #+#             */
/*   Updated: 2026/05/06 10:07:19 by idiaz-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

// Comprueba si line empieza con prefix
static int	starts_with(char *line, char *prefix)
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

// Parsea color F 220,100,0
static void	parse_color(char *line, int rgb[3])
{
	int	i;

	i = 0;
	while (*line && (*line < '0' || *line > '9'))
		line++; // saltar 'F ' o 'C '
	for (i = 0; i < 3; i++)
	{
		rgb[i] = atoi(line);
		if (rgb[i] < 0 || rgb[i] > 255)
		{
			printf("Error: invalid color\n");
			exit(1);
		}
		while (*line >= '0' && *line <= '9')
			line++;
		if (*line == ',')
			line++;
	}
}

// Parsea la configuración y llena la estructura t_game
void	parse_config(char **config, t_game *game)
{
	int		i;
	char	*line;

	i = 0;
	// Inicializar (MUY IMPORTANTE)
	game->no = NULL;
	game->so = NULL;
	game->we = NULL;
	game->ea = NULL;
	while (config[i])
	{
		line = config[i];
		// Saltar espacios al inicio
		while (*line == ' ')
			line++;
		// Ignorar líneas vacías
		if (*line == '\n' || *line == '\0')
		{
			i++;
			continue ;
		}
		if (starts_with(line, "NO "))
		{
			if (game->no)
				return (printf("Error: duplicate NO\n"), exit(1));
			game->no = extract_path(line);
			if (!game->no)
				return (printf("Error: malloc failed\n"), exit(1));
		}
		else if (starts_with(line, "SO "))
		{
			if (game->so)
				return (printf("Error: duplicate SO\n"), exit(1));
			game->so = extract_path(line);
			if (!game->so)
				return (printf("Error: malloc failed\n"), exit(1));
		}
		else if (starts_with(line, "WE "))
		{
			if (game->we)
				return (printf("Error: duplicate WE\n"), exit(1));
			game->we = extract_path(line);
			if (!game->we)
				return (printf("Error: malloc failed\n"), exit(1));
		}
		else if (starts_with(line, "EA "))
		{
			if (game->ea)
				return (printf("Error: duplicate EA\n"), exit(1));
			game->ea = extract_path(line);
			if (!game->ea)
				return (printf("Error: malloc failed\n"), exit(1));
		}
		else if (starts_with(line, "F "))
		{
			if (game->f[0] || game->f[1] || game->f[2])
				return (printf("Error: duplicate F\n"), exit(1));
			parse_color(line, game->f);
		}
		else if (starts_with(line, "C "))
		{
			if (game->c[0] || game->c[1] || game->c[2])
				return (printf("Error: duplicate C\n"), exit(1));
			parse_color(line, game->c);
		}
		else
		{
			return (printf("Error: invalid config line\n"), exit(1));
		}
		i++;
	}
	// Comprobación de faltantes
	if (!game->no || !game->so || !game->we || !game->ea)
		return (printf("Error: missing texture\n"), exit(1));
	// ⚠️ Esto es simple, luego puedes mejorarlo
	if (!game->f[0] && !game->f[1] && !game->f[2])
		return (printf("Error: missing floor color\n"), exit(1));
	if (!game->c[0] && !game->c[1] && !game->c[2])
		return (printf("Error: missing ceiling color\n"), exit(1));
}

