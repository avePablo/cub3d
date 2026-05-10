#ifndef CUB3D_H
# define CUB3D_H

# include "../MLX42/include/MLX42/MLX42.h"
# include "libft.h"
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdint.h> //para uint32_t(unisgned int de 32 bits)

# define WINDOW_WIDTH 1920
# define WINDOW_HEIGHT 1080

// ESTRUCTURA PARA RAYCASTING
typedef struct s_raycast
{
	double camera_x;       // Coordenada X en el espacio de la cámara
	double ray_dir_x;      // Dirección X del rayo
	double ray_dir_y;      // Dirección Y del rayo
	int map_x;             // Coordenada X del mapa (celda actual)
	int map_y;             // Coordenada Y del mapa (celda actual)
	double delta_x;       
		// Distancia que el rayo tiene que recorrer para pasar de una línea vertical a la siguiente
	double delta_y;       
		// Distancia que el rayo tiene que recorrer para pasar de una línea horizontal a la siguiente
	double side_x;         // Distancia al siguiente paso en dirección X
	double side_y;         // Distancia al siguiente paso en dirección Y
	int step_x;            // Paso en dirección X
	int step_y;            // Paso en dirección Y
	int side;              // Lado del muro que se ha colisionado
	double perp_wall_dist; // Distancia perpendicular al muro
	int line_height;       // Altura de la línea a dibujar
	int draw_start;        // Punto de inicio para dibujar
	int draw_end;          // Punto de final para dibujar
}		t_raycast;

// ESTRUCTURA PRINCIPAL DEL JUGADOR
typedef struct s_player
{
	double pos_x;   // Posición X del jugador
	double pos_y;   // Posición Y del jugador
	double dir_x;   // Dirección X del jugador
	double dir_y;   // Dirección Y del jugador
	double plane_x; // Plano de la cámara X (perpendicular a la dirección)
	double plane_y; // Plano de la cámara Y (perpendicular a la dirección)
}		t_player;

// ESTRUCTURA PRINCIPAL DEL JUEGO
typedef struct s_game
{
	char **map;       // Mapa del juego
	char *no;         // Ruta de la textura norte
	char *so;         // Ruta de la textura sur
	char *we;         // Ruta de la textura oeste
	char *ea;         // Ruta de la textura este
	mlx_texture_t *tex_no; // Textura norte cargada
	mlx_texture_t *tex_so; // Textura sur cargada
	mlx_texture_t *tex_we; // Textura oeste cargada
	mlx_texture_t *tex_ea; // Textura este cargada
	int f[3];         // Color del piso (RGB)
	int c[3];         // Color del techo (RGB)
	uint32_t floor_color;   // Color del piso en formato RGBA
	uint32_t ceiling_color; // Color del techo en formato RGBA
	int map_width;    // Ancho del mapa
	int map_height;   // Alto del mapa
	mlx_t *mlx;       // Contexto de MLX
	mlx_image_t *img; // Imagen para renderizar el juego
	t_player player;  // Información del jugador (posición, dirección, plano)
}		t_game;

char	**read_file(char *filename);
int     check_extension(char *filename);
void	split_file(char **file, char ***config, char ***map);
void	parse_config(char **config, t_game *game);
void	raycast(t_game *g);
void	validate_player(char **map);    
		// Valida que haya exactamente un jugador en el mapa
void	validate_map_closed(char **map);
		// Valida que el mapa esté cerrado (no haya espacios vacíos alrededor de los pasillos)
void    validate_textures(t_game *game); // Valida que las rutas de las texturas sean correctas
void	load_textures(t_game *game); // Carga las texturas usando MLX
uint32_t	get_texture_pixel(mlx_texture_t *tex, int x, int y);
int		is_config_line(char *line);
int		is_map_line(char *line);
int		is_empty_line(char *line);
int		is_valid_cell(char **map, int y, int x);
void	init_player_from_map(t_game *g);
		// Inicializa la posición y dirección del jugador a partir del mapa
void	init_ray(t_game *g, t_raycast *r, int x);
void	init_dda(t_game *g, t_raycast *r);
void	perform_dda(t_game *g, t_raycast *r);
void	draw_column(t_game *g, t_raycast *r, int x);
void	get_line_height(t_game *g, t_raycast *r);
void	put_pixel(mlx_image_t *img, int x, int y, uint32_t color);
uint32_t	rgb_to_hex(int r, int g, int b);
char	get_cell(t_game *g, int x, int y);
int		init_map(int argc, char **argv, t_game *game); // Lee el mapa, lo valida y lo guarda en la estructura del juego
int		init_mlx(t_game *game);
void	handle_input(t_game *g);

#endif
