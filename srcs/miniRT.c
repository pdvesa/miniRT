//
// Created by Jules Cayot on 13/05/2024.
//

#include <miniRT.h>

// int	miniRT(char *filename)
// {
// 	mlx_t			*mlx;
// 	t_scene	scene;
// 	int 			result;

// 	scene = parse_file(filename);
// 	if (!scene.camera)
// 		return (1);
// 	result = 1;
// 	mlx = mlx_init(WIDTH, HEIGHT, "miniRT", true);
// 	if (mlx)
// 	{
// 		mlx_loop_hook(mlx, &close_hook, mlx);
// 		result = render_scene(mlx, &scene);
// 		mlx_terminate(mlx);
// 	}
// 	else
// 		ft_putmlx_error();
// 	free_render_scene(&scene);
// 	return (result);
// }


// for parsing testing
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
