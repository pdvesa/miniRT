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

//#include <miniRT_render.h>
//#include <miniRT_parsing.h>
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
			return (ft_strarray_free(input_arr), ft_putendl_fd("Follow the damn instructions\n", 2));
		scene->camera->vector = vector;
	}
	else if (!(ft_strncmp(input_arr[0], "cord", 5)))
	{
		if (extract_cords(&cords, input_arr[1]))
			return (ft_strarray_free(input_arr), ft_putendl_fd("Follow the damn instructions\n", 2));
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
	{
		if (extract_cords(&cords, input_arr[1]))
			return (ft_strarray_free(input_arr), ft_putendl_fd("Follow the damn instructions\n", 2));
		object->center = cords;
	}
	else if (!(ft_strncmp(input_arr[0], "dia", 3)))
	{
		dia = get_numbers(input_arr[1], 1);
		if (dia < 0.0F || dia > HEIGHT)
			return (ft_strarray_free(input_arr), ft_putendl_fd("Follow the damn instructions\n", 2));
		object->diameter = dia;
	}
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
	{
		if (extract_cords(&cords, input_arr[1]))
			return (ft_strarray_free(input_arr), ft_putendl_fd("Follow the damn instructions\n", 2));
		object->coordinates = cords;
	}
	else if (!(ft_strncmp(input_arr[0], "orient", 7)))
	{
		if (extract_vector(&vector, input_arr[1]))
			return (ft_strarray_free(input_arr), ft_putendl_fd("Follow the damn instructions\n", 2));
		object->vector = vector;
	}
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
	{
		if (extract_cords(&cords, input_arr[1]))
			return (ft_strarray_free(input_arr), ft_putendl_fd("Follow the damn instructions\n", 2));
		object->center = cords;
	}
	else if (!(ft_strncmp(input_arr[0], "orient", 7)))
	{
		if (extract_vector(&vector, input_arr[1]))
			return (ft_strarray_free(input_arr), ft_putendl_fd("Follow the damn instructions\n", 2));
		object->vector = vector;
	}
	else if	(!(ft_strncmp(input_arr[0], "hgt", 4)))
	{
		height = get_numbers(input_arr[1], 1);
		if (height < 0.0F || height > HEIGHT)
			return (ft_strarray_free(input_arr), ft_putendl_fd("Follow the damn instructions\n", 2));
		object->height = height;
	}
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
	printf("test object you monkey %d\n", object_ray.inter_point.object_type);
	if (object_ray.inter_point.object_type == 3)
		mod_sphere((t_sphere *)(object_ray.inter_point.object));
	else if (object_ray.inter_point.object_type == 4)
		mod_plane((t_plane *)(object_ray.inter_point.object));
	else if (object_ray.inter_point.object_type == 5)
		mod_cyka((t_cylinder *)(object_ray.inter_point.object));
}