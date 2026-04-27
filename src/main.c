#include "cub3D.h"

static void init_game(t_game *game)
{
	game->player.pos_x = 0;
	game->player.pos_y = 0;

	game->player.dir_x = -1;
	game->player.dir_y = 0;

	game->player.plane_x = 0;
	game->player.plane_y = 0.66;
}

static void render(void *param)
{
	t_game *g;

	g = (t_game *)param;
	raycast(g);
}

int	main(int argc, char **argv)
{
	char	**file;
	char	**config;
	char	**map;
	t_game	game;
	mlx_t	*mlx;

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

	init_game(&game);

	mlx = mlx_init(800, 600, "Cub3D", true);
	if (!mlx)
		return (ft_putstr_fd("Error MLX\n", 2), 1);

	game.mlx = mlx;

	mlx_loop_hook(mlx, render, &game);
	mlx_loop(mlx);

	mlx_terminate(mlx);
	return (0);
}