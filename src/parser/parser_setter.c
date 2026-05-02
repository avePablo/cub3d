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

// Extrae ruta: "NO ./a.png" -> "./a.png"
static char	*extract_path(char *line)
{
	while (*line && *line != ' ')
		line++;
	while (*line == ' ')
		line++;
	return (ft_strdup(line)); // strdup para reservar memoria
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
		while (*line >= '0' && *line <= '9')
			line++;
		if (*line == ',')
			line++;
	}
}

// Parsea la configuración y llena la estructura t_game
void	parse_config(char **config, t_game *game)
{
	for (int i = 0; config[i]; i++)
	{
		if (starts_with(config[i], "NO "))
			game->no = extract_path(config[i]);
		else if (starts_with(config[i], "SO "))
			game->so = extract_path(config[i]);
		else if (starts_with(config[i], "WE "))
			game->we = extract_path(config[i]);
		else if (starts_with(config[i], "EA "))
			game->ea = extract_path(config[i]);
		else if (starts_with(config[i], "F "))
			parse_color(config[i], game->f);
		else if (starts_with(config[i], "C "))
			parse_color(config[i], game->c);
		else
		{
			// Líneas vacías o inválidas se ignoran
		}
	}
}
