/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_setter.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfuto <kfuto@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/02 19:00:14 by kfuto             #+#    #+#             */
/*   Updated: 2026/05/14 16:10:09 by kfuto            ###   ########.fr       */
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
	while (i < 3)
	{
		if (!ft_isdigit(*line))
		{
			ft_putstr_fd("Error: Invalid color\n", 2);
			exit(1);
		}
		rgb[i] = ft_atoi(line);
		if (rgb[i] < 0 || rgb[i] > 255)
		{
			ft_putstr_fd("Error: Color out of range\n", 2);
			exit(1);
		}
		while (ft_isdigit(*line))
			line++;
		if (i < 2)
		{
			if (*line != ',')
			{
				ft_putstr_fd("Error: Invalid color format\n", 2);
				exit(1);
			}
			line++;
		}
		i++;
	}
	while (*line == ' ' || *line == '\n')
		line++;
	if (*line != '\0')
	{
		ft_putstr_fd("Error: Extra characters after color values\n", 2);
		exit(1);
	}
}

// funcion que convierte RGB a RGBA (añadiendo el canal alpha con valor 255)
uint32_t	rgb_to_hex(int r, int g, int b)
{
	/* El formato RGBA se representa como 0xRRGGBBAA,
	donde AA es el canal alpha, desplazado 8 bits a la izquierda.
	el 255 representa el valor del canal alpha(transparencia total)*/
	return ((r << 24) | (g << 16) | (b << 8) | 255);
}

// Parsea la configuración y llena la estructura t_game
void	parse_config(char **config, t_game *game)
{
	int		i;
	int		has_f;
	int		has_c;
	char	*line;

	i = 0;
	has_f = 0;
	has_c = 0;
	// Inicializar texturas
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
			if (has_f)
				return (printf("Error: duplicate F\n"), exit(1));
			parse_color(line, game->f);
			has_f = 1;
		}
		else if (starts_with(line, "C "))
		{
			if (has_c)
				return (printf("Error: duplicate C\n"), exit(1));
			parse_color(line, game->c);
			has_c = 1;
		}
		else
			return (printf("Error: invalid config line\n"), exit(1));
		i++;
	}
	// Comprobar faltantes
	if (!game->no || !game->so || !game->we || !game->ea)
		{free_game(game);
		return (printf("Error: missing texture\n"), exit(1));}
	if (!has_f)
		{free_game(game);
		return (printf("Error: missing floor color\n"), exit(1));}
	if (!has_c)
		{free_game(game);
		return (printf("Error: missing ceiling color\n"), exit(1));}
	// Convertir RGB -> HEX RGBA
	game->floor_color = rgb_to_hex(game->f[0], game->f[1], game->f[2]);
	game->ceiling_color = rgb_to_hex(game->c[0], game->c[1], game->c[2]);
}
