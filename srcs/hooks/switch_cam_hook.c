//
// Created by jules on 12/06/2024.
//

# include <miniRT_hooks.h>

int	update_cam_index(mlx_key_data_t keydata, int cam_index, int cam_n)
{
	if (keydata.key == MLX_KEY_RIGHT && keydata.action == MLX_PRESS)
	{
		if (cam_index < cam_n - 1)
			cam_index++;
		else
			cam_index = 0;
	}
	if (keydata.key == MLX_KEY_LEFT && keydata.action == MLX_PRESS)
	{
		if (cam_index > 0)
			cam_index--;
		else
			cam_index = cam_n - 1;
	}
	return (cam_index);
}

void	switch_cam_hook(mlx_key_data_t keydata, void* param)
{
	mlx_t		*mlx;
	mlx_image_t	**render_images;
	t_scene		*render_scene;
	static int	cam_index = 0;
	int 		new_cam_index;

	mlx = ((t_switch_cam_hook_param *) param)->mlx;
	render_images = ((t_switch_cam_hook_param *) param)->render_images;
	render_scene = ((t_switch_cam_hook_param*) param)->render_scene;
	new_cam_index = update_cam_index(keydata, cam_index,
					ft_array_len(render_scene->camera));
	if (new_cam_index != cam_index)
	{
		cam_index = new_cam_index;
		if (!switch_cam(mlx, render_images, render_scene, cam_index))
			mlx_close_window(mlx);
	}

}

void	add_switch_cam_hook(t_switch_cam_hook_param *param,
							mlx_t *mlx, mlx_image_t **images, t_scene *scene)
{
	param->mlx = mlx;
	param->render_images = images;
	param->render_scene = scene;
	mlx_key_hook(mlx, &switch_cam_hook, param);
}
