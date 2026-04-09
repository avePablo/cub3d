#include "cub3D.h"

int	main(int argc, char **argv)
{
	char **file; // Array de strings con el contenido del archivo
	char **config; // Array de strings con la configuración (texturas, colores, etc.)
	char **map; // Array de strings con el mapa (líneas que representan el mapa)
	//int i = 0;

	if (argc != 2)
	{
		ft_putstr_fd("Error: Invalid number of arguments\n", 2);
		return (1);
	}

	file = read_file(argv[1]);
	if (!file)
	{
		ft_putstr_fd("Error: Could not read file\n", 2);
		return (1);
	}

	/*while (file[i])
	{
		printf("%s", file[i]);
		i++;
	}*/

	// Separar configuración y mapa
	split_file(file, &config, &map);

	//PRUEBAS DEL SPLIT_FILE
	printf("---- CONFIG ----\n");
	for (int i = 0; config[i]; i++)
    printf("%s", config[i]);

	printf("\n---- MAP ----\n");
	for (int i = 0; map[i]; i++)
    printf("%s\n", map[i]);

	//PRUEBAS DEL PARSE_CONFIG
	t_game game;
	game.map = map; // Guardar el mapa en la estructura del juego
	parse_config(config, &game);

	printf("NO: %s\n", game.no);
	printf("SO: %s\n", game.so);
	printf("WE: %s\n", game.we);
	printf("EA: %s\n", game.ea);
	printf("F: %d,%d,%d\n", game.f[0], game.f[1], game.f[2]);
	printf("C: %d,%d,%d\n", game.c[0], game.c[1], game.c[2]);
	//ventana de la mlx

	mlx_t *mlx = mlx_init(800, 600, "Cub3D", true);  // ancho, alto, título, vsync
    if (!mlx)
    {
        ft_putstr_fd("Error: Could not initialize MLX42\n", 2);
        return 1;
    }

    mlx_loop(mlx); 			// Mantener la ventana abierta

    mlx_terminate(mlx);		// Limpiar recursos al cerrar

    return 0;
}

