/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modifiers.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svesa <svesa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 16:52:37 by svesa             #+#    #+#             */
/*   Updated: 2024/06/07 16:07:59 by svesa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT_trans.h>

void	modify_statics(t_scene *scene, int key)
{
	char			**input_arr;
	t_coordinates	cords;
	t_vector		vector;

	input_arr = sanitize_input();
	if (!input_arr)
		return (ft_putendl_fd("Follow the damn instructions\n", 2));
	if (!(ft_strncmp(input_arr[0], "orient", 7)) && key == MLX_KEY_C)
	{
		if (extract_vector(&vector, input_arr[1]))
			return (translate_error(input_arr));
		scene->camera->vector = vector;
	}
	else if (!(ft_strncmp(input_arr[0], "cord", 5)))
	{
		if (extract_cords(&cords, input_arr[1]))
			return (translate_error(input_arr));
		if (key == MLX_KEY_C)
			scene->camera->center = cords;
		else if (key == MLX_KEY_L)
			scene->light->center = cords;
	}
	else
		ft_putendl_fd("Follow the damn instructions\n", 2);
	ft_strarray_free(input_arr);
}

void	mod_sphere(t_sphere *object)
{
	char			**input_arr;
	t_coordinates	cords;
	float			dia;

	input_arr = sanitize_input();
	if (!input_arr)
		return (ft_putendl_fd("Follow the damn instructions\n", 2));
	if (!(ft_strncmp(input_arr[0], "cord", 5)))
		object->center = *(t_coordinates *)get_value((void *)&(object->center),
				(void *)&cords, input_arr[1], 1);
	else if (!(ft_strncmp(input_arr[0], "dia", 3)))
		object->diameter = *(float *)get_value((void *)&(object->diameter),
				(void *)&dia, input_arr[1], 3);
	else
		ft_putendl_fd("Follow the damn instructions\n", 2);
	ft_strarray_free(input_arr);
}

void	mod_plane(t_plane *object)
{
	char			**input_arr;
	t_coordinates	cords;
	t_vector		vector;

	input_arr = sanitize_input();
	if (!input_arr)
		return (ft_putendl_fd("Follow the damn instructions\n", 2));
	if (!(ft_strncmp(input_arr[0], "cord", 5)))
		object->coordinates = *(t_coordinates *)get_value(
				(void *)&(object->coordinates),
				(void *)&cords, input_arr[1], 1);
	else if (!(ft_strncmp(input_arr[0], "orient", 7)))
		object->vector = *(t_vector *)get_value((void *)&(object->vector),
				(void *)&vector, input_arr[1], 2);
	else
		ft_putendl_fd("Follow the damn instructions\n", 2);
	ft_strarray_free(input_arr);
}

void	mod_cyka(t_cylinder *object)
{
	char			**input_arr;
	t_coordinates	cords;
	t_vector		vector;
	float			height;

	input_arr = sanitize_input();
	if (!input_arr)
		return (ft_putendl_fd("Follow the damn instructions\n", 2));
	if (!(ft_strncmp(input_arr[0], "cord", 5)))
		object->center = *(t_coordinates *)get_value((void *)&(object->center),
				(void *)&cords, input_arr[1], 1);
	else if (!(ft_strncmp(input_arr[0], "orient", 7)))
		object->vector = *(t_vector *)get_value((void *)&(object->vector),
				(void *)&vector, input_arr[1], 2);
	else if (!(ft_strncmp(input_arr[0], "hgt", 4)))
		object->height = *(float *)get_value((void *)&(object->height),
				(void *)&height, input_arr[1], 3);
	else
		ft_putendl_fd("Follow the damn instructions\n", 2);
	ft_strarray_free(input_arr);
}

void	modify_objects(t_hook_container *data)
{
	int32_t				x;
	int32_t				y;
	t_pixel_cdts		pixel;
	t_viewport			view;
	t_ray				object_ray;

	view = initialise_viewport(data->image, data->scene->camera);
	x = 0;
	y = 0;
	mlx_get_mouse_pos(data->mlx, &x, &y);
	printf("x %d y %d\n", (int)x, (int)y);
	pixel.x = x;
	pixel.y = y;
	object_ray = ray_to_object(data->scene, &view, &pixel);
	printf("test object you monkey %d\n", object_ray.inter.object_type);
	if (object_ray.inter.object_type == 3)
		mod_sphere((t_sphere *)(object_ray.inter.object));
	else if (object_ray.inter.object_type == 4)
		mod_plane((t_plane *)(object_ray.inter.object));
	else if (object_ray.inter.object_type == 5)
		mod_cyka((t_cylinder *)(object_ray.inter.object));
}
