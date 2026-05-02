#ifndef CUB3D_H
# define CUB3D_H

# include "../MLX42/include/MLX42/MLX42.h"
# include "libft.h"
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_raycast
{
	double		camera_x;
	double		ray_dir_x;
	double		ray_dir_y;
	int			map_x;
	int			map_y;
	double		delta_x;
	double		delta_y;
	double		side_x;
	double		side_y;
	int			step_x;
	int			step_y;
	int			side;
	double		perp_wall_dist;
	int			line_height;
	int			draw_start;
	int			draw_end;
}				t_raycast;

typedef struct s_player
{
	double		pos_x;
	double		pos_y;
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;
}				t_player;

typedef struct s_game
{
	char		**map;
	char		*no;
	char		*so;
	char		*we;
	char		*ea;
	int			f[3];
	int			c[3];
	mlx_t		*mlx;
	mlx_image_t	*img;
	t_player	player;
}				t_game;

char			**read_file(char *filename);
void			split_file(char **file, char ***config, char ***map);
void			parse_config(char **config, t_game *game);
void			raycast(t_game *g);
void			validate_player(char **map);
void			validate_map_closed(char **map);
int				is_config_line(char *line);
int				is_map_line(char *line);
int				is_empty_line(char *line);
int				is_valid_cell(char **map, int y, int x);
void			init_player_from_map(t_game *g);
void			init_ray(t_game *g, t_raycast *r, int x);
void			init_dda(t_game *g, t_raycast *r);
void			perform_dda(t_game *g, t_raycast *r);
void			draw_column(t_game *g, t_raycast *r, int x);
void			get_line_height(t_game *g, t_raycast *r);
void			put_pixel(mlx_image_t *img, int x, int y, uint32_t color);
char			get_cell(t_game *g, int x, int y);
int				init_map(int argc, char **argv, t_game *game);
int				init_mlx(t_game *game);

#endif
