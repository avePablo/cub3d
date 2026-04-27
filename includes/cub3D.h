#ifndef CUB3D_H
# define CUB3D_H

# include <math.h>
# include "libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include "../MLX42/include/MLX42/MLX42.h"

typedef struct s_player
{
	double pos_x;
	double pos_y;

	double dir_x;
	double dir_y;

	double plane_x;
	double plane_y;
} t_player;

typedef struct s_game
{
	char	**map;
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	int		f[3];
	int		c[3];

	mlx_t	*mlx;
	mlx_image_t	*img;

	t_player	player;
}	t_game;

char	**read_file(char *filename);
void	split_file(char **file, char ***config, char ***map);
void	parse_config(char **config, t_game *game);
void	raycast(t_game *g);
void	validate_player(char **map);
void	validate_map_closed(char **map);
void	draw_column(t_game *g, int x, int start, int end, int side);
int		is_config_line(char *line);
int		is_map_line(char *line);
void	init_player_from_map(t_game *g);

#endif
