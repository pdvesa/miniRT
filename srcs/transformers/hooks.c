/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svesa <svesa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 16:52:37 by svesa             #+#    #+#             */
/*   Updated: 2024/06/07 16:07:59 by svesa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT_trans.h>

void	key_function(mlx_key_data_t keydata, void *param)
{
	t_hook_container	*data;
	static int			flag = 0;

	data = (t_hook_container *)param;
	if (flag == 0 && keydata.key != MLX_KEY_ESCAPE)
		print_instructions();
	flag = 1;
	if (keydata.key == MLX_KEY_A && keydata.action == MLX_PRESS)
		print_instructions();
	if (keydata.key == MLX_KEY_O && keydata.action == MLX_PRESS)
	{
		modify_objects(data);
		ft_re_render(data);
	}
	if ((keydata.key == MLX_KEY_C && keydata.action == MLX_PRESS)
		|| (keydata.key == MLX_KEY_L && keydata.action == MLX_PRESS))
	{
		modify_statics(data->scene, keydata.key);
		ft_re_render(data);
	}
}

//esc prints instructions also dont know if we exit properly in general

/*bool mlx_is_mouse_up(mlx_t* mlx, mouse_key_t key)
{
	//MLX_NONNULL(mlx);

	return (glfwGetMouseButton(mlx->window, key) == GLFW_RELEASE);
}

void	resize_function(int32_t width, int32_t height, void *param)
{
	t_hook_container	*data;
//	static int			count = 1;

	data = (t_hook_container *)param;
	while(1)
	{
		if ((mlx_is_mouse_up(data->mlx, MLX_MOUSE_BUTTON_LEFT)))
			break;
	}
	if (count % 2 != 0)
	{
		mlx_get_monitor_size(0, &width, &height);
		mlx_set_window_size(data->mlx, width, height);
		mlx_resize_image(data->image, width, height);
		//count++;
	}
	else
	{
		mlx_set_window_size(data->mlx, WIDTH, HEIGHT);
		mlx_resize_image(data->image, WIDTH, HEIGHT);
		count++;
	}
	sleep(1);
}*/

/*void	resize_function(int32_t width, int32_t height, void *param)
{
	t_hook_container	*data;

	(void)width;
	(void)height;
	data = (t_hook_container *)param;
	printf("stuff 1 %d %d\n", data->mlx->width, data->mlx->height);
//	if (data->mlx->height != HEIGHT && data->mlx->width != WIDTH)
//	{
		printf("stuff 2 %d %d\n", data->mlx->width, data->mlx->height);
//		mlx_set_window_size(data->mlx, data->mlx->width, data->mlx->height);
		mlx_resize_image(data->image, data->mlx->height , data->mlx->height);
		ray_trace(data->image, data->scene);
		if (mlx_image_to_window(data->mlx, data->image, 0, 0) == -1) // dont know if we can just re_render without deleting or do we need to make new image for not leaking
		{
			mlx_delete_image(data->mlx, data->image);
			ft_putmlx_error();
		}
//	}
}*/



