//
// Created by Jules Cayot on 13/05/2024.
//

#include <miniRT.h>

void	close_hook(void *param)
{
	mlx_t	*mlx;

	mlx = param;
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
}

int	miniRT(char *filename)
{
	mlx_t			*mlx;
	t_scene			scene;
	int 			result;

	scene = parse_file(filename);
	if (!scene.ambient_light)
		return (1);
	print_all(&scene);
	free_render_scene(&scene);
	return (0);
}

int	main(int n, char *args[])
{
	if (n != 2)
		return (1);
	return (miniRT(args[1]));
}
