//
// Created by Jules Cayot on 5/18/24.
//

#include <miniRT_render.h>

void	*clear_images(mlx_t *mlx, mlx_image_t **render_images)
{
	int	i;

	i = 0;
	while (render_images[i])
		mlx_delete_image(mlx, render_images[i]);
	free(render_images);
	return (NULL);
}

mlx_image_t	**initialize_images(mlx_t *mlx, size_t n_cam)
{
	mlx_image_t	**render_images;
	size_t		i;

	render_images = malloc(n_cam * sizeof (mlx_image_t*));
	if (!render_images)
		return (NULL);
	i = 0;
	while (i < n_cam)
	{
		render_images[i] = mlx_new_image(mlx, mlx -> width, mlx -> height);
		if (!render_images[i])
		{
			ft_putmlx_error();
			return (clear_images(mlx, render_images));
		}
		i++;
	}
	return (render_images);
}

int	render_scene(mlx_t *mlx, t_render_scene *scene)
{
	mlx_image_t	**render_images;

	render_images = initialize_images(mlx, ft_array_len(scene -> camera));
	if (!render_images)
		return (EXIT_FAILURE);
	ray_trace(render_images[0], scene, 0);
	if (mlx_image_to_window(mlx, render_images[0], 0, 0) != -1)
	{
		mlx_loop(mlx);
	}
	else
		ft_putmlx_error();
	clear_images(mlx, render_images);
	return (EXIT_SUCCESS);
}
