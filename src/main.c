#include "cub3D.h"

int	main(int argc, char **argv)
{
	char **file;
	int i = 0;

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

	while (file[i])
	{
		printf("%s", file[i]);
		i++;
	}

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
