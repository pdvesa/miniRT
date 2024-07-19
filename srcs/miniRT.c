/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcayot <jcayot.student@hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 21:01:02 by jcayot            #+#    #+#             */
/*   Updated: 2024/07/18 21:01:04 by jcayot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT.h>

void	close_hook(void *param)
{
	mlx_t	*mlx;

	mlx = param;
	if (mlx_is_key_down(mlx, MLX_KEY_ESCAPE))
		mlx_close_window(mlx);
}

int	minirt(char *filename)
{
	mlx_t	*mlx;
	t_scene	scene;
	int		result;

	scene = parse_file(filename);
	if (!scene.ambient_light)
		return (1);
	result = 1;
	mlx_set_setting(MLX_STRETCH_IMAGE, true);
	mlx = mlx_init(WIDTH, HEIGHT, "miniRT", true);
	if (mlx)
	{
		mlx_loop_hook(mlx, &close_hook, mlx);
		result = render_scene(mlx, &scene);
		mlx_terminate(mlx);
	}
	else
		ft_putmlx_error();
	free_render_scene(&scene);
	return (result);
}

int	main(int n, char *args[])
{
	if (n != 2)
		return (1);
	return (minirt(args[1]));
}
