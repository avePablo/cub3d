/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_config.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idiaz-ca <idiaz-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/02 19:00:14 by kfuto             #+#    #+#             */
/*   Updated: 2026/05/14 16:59:35 by idiaz-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	parse_element(char *line, t_game *game, int *has_f, int *has_c)
{
	if (starts_with(line, "NO "))
		parse_texture(line, &game->no, "NO");
	else if (starts_with(line, "SO "))
		parse_texture(line, &game->so, "SO");
	else if (starts_with(line, "WE "))
		parse_texture(line, &game->we, "WE");
	else if (starts_with(line, "EA "))
		parse_texture(line, &game->ea, "EA");
	else if (starts_with(line, "F "))
	{
		if (*has_f)
			return (printf("Error: duplicate F\n"), exit(1));
		parse_color(line, game->f);
		*has_f = 1;
	}
	else if (starts_with(line, "C "))
	{
		if (*has_c)
			return (printf("Error: duplicate C\n"), exit(1));
		parse_color(line, game->c);
		*has_c = 1;
	}
	else
		return (printf("Error: invalid config line\n"), exit(1));
}

static void	check_config(t_game *game, int has_f, int has_c)
{
	if (!game->no || !game->so || !game->we || !game->ea)
		return (printf("Error: missing texture\n"), exit(1));
	if (!has_f)
		return (printf("Error: missing floor color\n"), exit(1));
	if (!has_c)
		return (printf("Error: missing ceiling color\n"), exit(1));
	game->floor_color = rgb_to_hex(game->f[0], game->f[1], game->f[2]);
	game->ceiling_color = rgb_to_hex(game->c[0], game->c[1], game->c[2]);
}

void	parse_config(char **config, t_game *game)
{
	int		i;
	int		has_f;
	int		has_c;
	char	*line;

	i = 0;
	has_f = 0;
	has_c = 0;
	game->no = NULL;
	game->so = NULL;
	game->we = NULL;
	game->ea = NULL;
	while (config[i])
	{
		line = config[i];
		while (*line == ' ')
			line++;
		if (*line != '\n' && *line != '\0')
			parse_element(line, game, &has_f, &has_c);
		i++;
	}
	check_config(game, has_f, has_c);
}
