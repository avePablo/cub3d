/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idiaz-ca <idiaz-ca@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/13 19:42:01 by idiaz-ca          #+#    #+#             */
/*   Updated: 2026/05/19 10:53:25 by idiaz-ca         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../MLX42/include/MLX42/MLX42.h"
# include "libft.h"
# include <fcntl.h>
# include <math.h>
# include <stdint.h> // For uint32_t (32-bit unsigned integer)
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define WINDOW_WIDTH 1920
# define WINDOW_HEIGHT 1080

// RAYCASTING STRUCTURE
/*typedef struct s_raycast
{
	double camera_x;  // X coordinate in camera space
	double ray_dir_x; // Ray direction X
	double ray_dir_y; // Ray direction Y
	int map_x;        // X coordinate in the map (current cell)
	int map_y;        // Y coordinate in the map (current cell)
	double	delta_x; // Distance the ray has to travel to
						move from one vertical line to the next
	double	delta_y; // Distance the ray has to travel to
						move from one horizontal line to the next
	double side_x;         // Distance to the next step in X direction
	double side_y;         // Distance to the next step in Y direction
	int step_x;            // Step in X direction
	int step_y;            // Step in Y direction
	int side;              // Side of the wall that was hit
	double perp_wall_dist; // Perpendicular distance to the wall
	int line_height;       // Height of the line to draw
	int draw_start;        // Starting point for drawing
	int draw_end;          // Ending point for drawing
}			t_raycast;*/
typedef struct s_raycast
{
	double			camera_x;
	double			ray_dir_x;
	double			ray_dir_y;
	int				map_x;
	int				map_y;
	double			delta_x;
	double			delta_y;
	double			side_x;
	double			side_y;
	int				step_x;
	int				step_y;
	int				side;
	double			perp_wall_dist;
	int				line_height;
	int				draw_start;
	int				draw_end;
}					t_raycast;

// MAIN PLAYER STRUCTURE
/*typedef struct s_player
{
	double pos_x;   // Player X position
	double pos_y;   // Player Y position
	double dir_x;   // Player direction X
	double dir_y;   // Player direction Y
	double plane_x; // Camera plane X (perpendicular to direction)
	double plane_y; // Camera plane Y (perpendicular to direction)
}			t_player;*/
typedef struct s_player
{
	double			pos_x;
	double			pos_y;
	double			dir_x;
	double			dir_y;
	double			plane_x;
	double			plane_y;
}					t_player;

// MAIN GAME STRUCTURE
/*typedef struct s_game
{
	char **map;             // Game map
	char *no;               // North texture path
	char *so;               // South texture path
	char *we;               // West texture path
	char *ea;               // East texture path
	mlx_texture_t *tex_no;  // Loaded north texture
	mlx_texture_t *tex_so;  // Loaded south texture
	mlx_texture_t *tex_we;  // Loaded west texture
	mlx_texture_t *tex_ea;  // Loaded east texture
	int f[3];               // Floor color (RGB)
	int c[3];               // Ceiling color (RGB)
	uint32_t floor_color;   // Floor color in RGBA format
	uint32_t ceiling_color; // Ceiling color in RGBA format
	int map_width;          // Map width
	int map_height;         // Map height
	mlx_t *mlx;             // MLX context
	mlx_image_t *img;       // Image used to render the game
	t_player player;        // Player info (position,
							direction, plane)
}			t_game;*/
typedef struct s_game
{
	char			**map;
	char			*no;
	char			*so;
	char			*we;
	char			*ea;
	mlx_texture_t	*tex_no;
	mlx_texture_t	*tex_so;
	mlx_texture_t	*tex_we;
	mlx_texture_t	*tex_ea;
	int				f[3];
	int				c[3];
	uint32_t		floor_color;
	uint32_t		ceiling_color;
	int				map_width;
	int				map_height;
	mlx_t			*mlx;
	mlx_image_t		*img;
	t_player		player;
}					t_game;

char				**read_file(char *filename);
int					check_extension(char *filename);
void				split_file(char **file, char ***config, char ***map);
int					find_map_start(char **file);
int					starts_with(char *line, char *prefix);
void				parse_config(char **config, t_game *game);
void				parse_color(char *line, int rgb[3]);
void				parse_texture(char *line, char **texture, char *id);
void				raycast(t_game *g);
void				validate_map(t_game *game);
void				validate_player(char **map);
void				validate_map_closed(char **map);
void				validate_textures(t_game *game);
char				**make_map_rectangular(char **map);
void				load_textures(t_game *game);
uint32_t			get_texture_pixel(mlx_texture_t *tex, int x, int y);
int					is_config_line(char *line);
int					is_map_line(char *line);
int					is_empty_line(char *line);
int					is_valid_cell(char **map, int y, int x);
void				init_player_from_map(t_game *g);
void				init_ray(t_game *g, t_raycast *r, int x);
void				init_dda(t_game *g, t_raycast *r);
void				perform_dda(t_game *g, t_raycast *r);
void				draw_column(t_game *g, t_raycast *r, int x);
void				get_line_height(t_game *g, t_raycast *r);
void				put_pixel(mlx_image_t *img, int x, int y, uint32_t color);
uint32_t			rgb_to_hex(int r, int g, int b);
char				get_cell(t_game *g, int x, int y);
int					init_map(int argc, char **argv, t_game *game);
int					init_mlx(t_game *game);
void				handle_input(t_game *g);
void				free_array(char **arr);
void				free_game(t_game *game);

#endif
