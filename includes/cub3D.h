#include "libft.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "../MLX42/include/MLX42/MLX42.h"

#ifndef CUB3D_H
# define CUB3D_H

typedef struct s_game
{
    char *no; // Ruta de la textura norte
    char *so; // Ruta de la textura sur
    char *we; // Ruta de la textura oeste
    char *ea; // Ruta de la textura este
    int  f[3]; // Color del suelo (RGB)
    int  c[3]; // Color del techo (RGB)
    char **map; // Mapa representado como un array de strings
}   t_game;

char	**read_file(char *filename);
void	split_file(char **file, char ***config, char ***map);
void    parse_config(char **config, t_game *game);
#endif
