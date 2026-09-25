/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_color.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idiaz-ca <idiaz-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/14 16:57:53 by idiaz-ca          #+#    #+#             */
/*   Updated: 2026/05/14 17:00:59 by idiaz-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static int	get_rgb_value(char **line)
{
	int	value;

	if (!ft_isdigit(**line))
	{
		ft_putstr_fd("Error: Invalid color\n", 2);
		exit(1);
	}
	value = ft_atoi(*line);
	if (value < 0 || value > 255)
	{
		ft_putstr_fd("Error: Color out of range\n", 2);
		exit(1);
	}
	while (ft_isdigit(**line))
		(*line)++;
	return (value);
}

void	parse_color(char *line, int rgb[3])
{
	int	i;

	i = 0;
	while (*line && (*line < '0' || *line > '9'))
		line++;
	while (i < 3)
	{
		rgb[i] = get_rgb_value(&line);
		if (i < 2 && *line++ != ',')
		{
			ft_putstr_fd("Error: Invalid color format\n", 2);
			exit(1);
		}
		i++;
	}
	while (*line == ' ' || *line == '\n')
		line++;
	if (*line)
	{
		ft_putstr_fd("Error: Extra characters after color values\n", 2);
		exit(1);
	}
}

/* Converts RGB to RGBA (adding an alpha channel with value 255)
	The RGBA format is represented as 0xRRGGBBAA,
	where AA is the alpha channel shifted 8 bits to the left.
	255 represents the alpha value (fully opaque). */
uint32_t	rgb_to_hex(int r, int g, int b)
{
	return ((r << 24) | (g << 16) | (b << 8) | 255);
}
