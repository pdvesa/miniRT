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

mlx_t	*initialize_mlx(mlx_image_t **image)
{
	mlx_t	*mlx;

	mlx = mlx_init(WIDTH, HEIGHT, "miniRT", false);
	if (!mlx)
		return (ft_putmlx_error());
	mlx_loop_hook(mlx, &close_hook, mlx);
	*image = mlx_new_image(mlx, WIDTH, HEIGHT);
	if (!(*image))
	{
		mlx_terminate(mlx);
		return (ft_putmlx_error());
	}
	if (mlx_image_to_window(mlx, *image, 0, 0) == -1)
	{
		mlx_delete_image(mlx, *image);
		mlx_terminate(mlx);
		return (ft_putmlx_error());
	}
	return (mlx);
}

int	minirt(char *filename)
{
	mlx_t		*mlx;
	mlx_image_t	*image;
	t_scene		scene;
	int			result;

	scene = parse_file(filename);
	if (!scene.am_light)
		return (1);
	result = 1;
	mlx = initialize_mlx(&image);
	if (mlx)
	{
		result = render_scene(&scene, image);
		mlx_loop(mlx);
		mlx_delete_image(mlx, image);
		mlx_terminate(mlx);
	}
	free_render_scene(&scene);
	return (result);
}

int	main(int n, char *args[])
{
	if (n != 2)
		return (1);
	return (minirt(args[1]));
}
