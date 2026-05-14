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

// funcion que convierte RGB a RGBA (añadiendo el canal alpha con valor 255)
/* El formato RGBA se representa como 0xRRGGBBAA,
	donde AA es el canal alpha, desplazado 8 bits a la izquierda.
	el 255 representa el valor del canal alpha(transparencia total)*/
uint32_t	rgb_to_hex(int r, int g, int b)
{
	return ((r << 24) | (g << 16) | (b << 8) | 255);
}
