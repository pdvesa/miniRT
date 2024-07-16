/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extractors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svesa <svesa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 20:23:25 by svesa             #+#    #+#             */
/*   Updated: 2024/06/07 16:05:37 by svesa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT_parsing.h>
#include <ft_maths.h>

int	extract_rgb(t_rgb *colors, char *content)
{
	char	**temp_array;
	int		error;

	error = 0;
	temp_array = ft_split(content, ',');
	if (!temp_array)
		return (EXIT_FAILURE);
	if (ft_strarray_len(temp_array) != 3)
		return (ft_strarray_free(temp_array), EXIT_FAILURE);
	colors->r = get_numbers(temp_array[0], 0);
	if (colors->r > 255 || colors->r < 0)
		error = 1;
	colors->g = get_numbers(temp_array[1], 0);
	if (colors->g > 255 || colors->g < 0)
		error = 1;
	colors->b = get_numbers(temp_array[2], 0);
	if (colors->b > 255 || colors->b < 0)
		error = 1;
	ft_strarray_free(temp_array);
	if (error)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	extract_vector(t_vector *vector, char *content)
{
	char	**temp_array;
	int		error;

	error = 0;
	temp_array = ft_split(content, ',');
	if (!temp_array)
		return (EXIT_FAILURE);
	if (ft_strarray_len(temp_array) != 3)
		return (ft_strarray_free(temp_array), EXIT_FAILURE);
	vector->x = get_numbers(temp_array[0], 1);
	if (vector->x > 1.0F || vector->x < -1.0F)
		error = 2;
	vector->y = get_numbers(temp_array[1], 1);
	if (vector->y > 1.0F || vector->y < -1.0F)
		error = 2;
	vector->z = get_numbers(temp_array[2], 1);
	if (vector->z > 1.0F || vector->z < -1.0F)
		error = 2;
	ft_strarray_free(temp_array);
	if (error)
		return (EXIT_FAILURE);
	*vector = normalize_vector(*vector);
	return (EXIT_SUCCESS);
}

int	extract_cords(t_coordinates *cords, char *content)
{
	char	**temp_array;
	int		error;

	error = 0;
	temp_array = ft_split(content, ',');
	if (!temp_array)
		return (EXIT_FAILURE);
	if (ft_strarray_len(temp_array) != 3)
		return (ft_strarray_free(temp_array), EXIT_FAILURE);
	cords->x = get_numbers(temp_array[0], 1);
	if (cords->x > 1000.0F || cords->x < -1000.0F) //no idea for limits here
		error = 3;
	cords->y = get_numbers(temp_array[1], 1);
	if (cords->y > 1000.0F || cords->y < -1000.0F)
		error = 3;
	cords->z = get_numbers(temp_array[2], 1);
	if (cords->z > 1000.0F || cords->z < -1000.0F)
		error = 3;
	ft_strarray_free(temp_array);
	if (error)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	save_vector(t_scene *scene, char *content_str, int obj_type, int i)
{
	if (obj_type == C)
	{
		if (extract_vector(&(scene->camera->vector), content_str))
			return (EXIT_FAILURE);
	}
	else if (obj_type == pl)
	{
		if (extract_vector(&(scene->plane[i]->vector), content_str))
			return (EXIT_FAILURE);
	}
	else if (obj_type == cyka)
	{
		if (extract_vector(&(scene->cylinder[i]->vector), content_str))
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	save_cords(t_scene *scene, char *content_str, int obj_type, int i)
{
	if (obj_type == C)
	{
		if (extract_cords(&(scene->camera->center), content_str))
			return (EXIT_FAILURE);
	}
	else if (obj_type == L)
	{
		if (extract_cords(&(scene->light->center), content_str))
			return (EXIT_FAILURE);
	}
	else if (obj_type == sp)
	{
		if (extract_cords(&(scene->sphere[i])->center, content_str))
			return (EXIT_FAILURE);
	}
	else if (obj_type == pl)
	{
		if (extract_cords(&(scene->plane[i])->coordinates, content_str))
			return (EXIT_FAILURE);
	}
	else if (obj_type == cyka)
	{
		if (extract_cords(&(scene->cylinder[i])->center, content_str))
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

// int	save_cords(t_scene *scene, char *content_str, int obj_type, int i)
// {
// 	t_coordinates	*cords_array[3] = {&(scene->cam->center), &(scene->light->center), &(scene->sphere[i]->center)};

// 	printf("str %s and obj %d and i %d\n", content_str, obj_type, i);
// 	if (extract_cords(cords_array[obj_type - 1], content_str))
// 			return (EXIT_FAILURE);
// 	return (EXIT_SUCCESS);
// }
