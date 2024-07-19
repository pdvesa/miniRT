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

int	display_render(mlx_t *mlx, void *render)
{
	mlx_image_t				*mlx_image;

	mlx_image = mlx_new_image(mlx, mlx -> width, mlx -> height);
	if (!mlx_image)
		return (ft_putmlx_error());
	ft_memcpy(mlx_image->pixels, render,
		mlx->width * mlx->height * sizeof (uint32_t));
	if (mlx_image_to_window(mlx, mlx_image, 0, 0) == -1)
	{
		mlx_delete_image(mlx, mlx_image);
		return (ft_putmlx_error());
	}
	mlx_loop(mlx);
	mlx_delete_image(mlx, mlx_image);
	return (EXIT_SUCCESS);
}

mlx_t	*initialize_mlx(void)
{
	mlx_t	*mlx;

	mlx_set_setting(MLX_STRETCH_IMAGE, true);
	mlx = mlx_init(WIDTH, HEIGHT, "miniRT", true);
	if (!mlx)
	{
		ft_putmlx_error();
		return (NULL);
	}
	mlx_loop_hook(mlx, &close_hook, mlx);
	return (mlx);
}

int	minirt(char *filename)
{
	mlx_t	*mlx;
	t_scene	scene;
	void	*render;
	int		result;

	scene = parse_file(filename);
	if (!scene.ambient_light)
		return (1);
	result = 1;
	render = ray_trace(&scene, WIDTH, HEIGHT);
	if (render)
	{
		mlx = initialize_mlx();
		if (mlx)
		{
			result = display_render(mlx, render);
			mlx_terminate(mlx);
		}
		free(render);
	}
	else
		ft_putendl_fd("MiniRT : Malloc error", 2);
	free_render_scene(&scene);
	return (result);
}

int	main(int n, char *args[])
{
	if (n != 2)
		return (1);
	return (minirt(args[1]));
}
