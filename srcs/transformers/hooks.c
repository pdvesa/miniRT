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

