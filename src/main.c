#include "cub3D.h"

static void	render(void *param)
{
	t_game	*g;

	g = (t_game *)param;
	raycast(g);
}

int	main(int argc, char **argv)
{
	char **file;
	char **config;
	char **map;
	t_game game;
	mlx_t *mlx;

	if (argc != 2)
		return (ft_putstr_fd("Error\n", 2), 1);
	ft_memset(&game, 0, sizeof(t_game));
	file = read_file(argv[1]);
	if (!file)
		return (ft_putstr_fd("Error\n", 2), 1);
	split_file(file, &config, &map);
	game.map = map;
	// 1. parse config primero
	parse_config(config, &game);
	// 2. validar mapa ANTES de modificarlo
	validate_player(map);
	validate_map_closed(map);
	// 3. ahora sí inicializas player (esto modifica el mapa)
	init_player_from_map(&game);
	// init_game(&game);
	mlx = mlx_init(800, 600, "Cub3D", true);
	if (!mlx)
		return (ft_putstr_fd("Error MLX\n", 2), 1);
	game.mlx = mlx;
	game.img = mlx_new_image(mlx, 800, 600);
	if (!game.img)
		return (ft_putstr_fd("Error imagen\n", 2), 1);
	if (mlx_image_to_window(mlx, game.img, 0, 0) < 0)
		return (ft_putstr_fd("Error window\n", 2), 1);
	mlx_loop_hook(mlx, render, &game);
	mlx_loop(mlx);
	mlx_terminate(mlx);
	return (0);
}