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
	if (vector->x == 0.0F && vector->y == 0.0F && vector->z == 0.0F)
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
	if (cords->x > 1000.0F || cords->x < -1000.0F)
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

int	save_cords(t_scene *scene, char *cnt_str, int obj_type, int i)
{
	const void	*cords_array[2] = {&(scene->camera->center),
		&(scene->light->center)};
	void		*temp_cord;

	if (obj_type == C || obj_type == L)
	{
		if (extract_cords((t_coordinates *)cords_array[obj_type - 1], cnt_str))
			return (EXIT_FAILURE);
	}
	else
	{
		if (obj_type == sp)
			temp_cord = &(scene->sphere[i])->center;
		if (obj_type == pl)
			temp_cord = &(scene->plane[i])->coordinates;
		if (obj_type == cyka)
			temp_cord = &(scene->cylinder[i])->center;
		if (extract_cords((t_coordinates *)temp_cord, cnt_str))
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int	erreur_dictateur(char **array, int obj_type)
{
	ft_strarray_free(array);
	extract_error(obj_type);
	return (EXIT_FAILURE);
}
