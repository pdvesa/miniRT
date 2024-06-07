/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_extractors.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svesa <svesa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 15:58:09 by svesa             #+#    #+#             */
/*   Updated: 2024/06/07 16:04:11 by svesa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT_parsing.h>

int	extract_sphere(t_scene *scene, char **content, int i)
{
	char	*content_str;
	char	**cont_arr;

	content_str = find_content_str(content, "sp"); //fix later
	cont_arr = ft_split(content_str, ' ');
	ft_memset(content_str, 0, ft_strlen(content_str));
	if (!cont_arr)
		return (EXIT_FAILURE);
	if (cont_arr[4])
		return (ft_strarray_free(cont_arr), extract_error(sp), EXIT_FAILURE);
	if (save_cords(scene, cont_arr[1], sp, i))
		return (ft_strarray_free(cont_arr), EXIT_FAILURE);
	scene->sphere[i]->diameter = get_numbers(cont_arr[2], 1);
	if (scene->sphere[i]->diameter < -100.0F
		|| scene->ambient_light->ratio > 100.0F) //no idea about limit
		return (ft_strarray_free(cont_arr), extract_error(sp), EXIT_FAILURE);
	if (extract_rgb(&(scene->sphere[i]->rgb), cont_arr[3]))
	{
		ft_strarray_free(cont_arr);
		return (extract_error(sp), EXIT_SUCCESS);
	}
	return (ft_strarray_free(cont_arr), EXIT_SUCCESS);
}

int	extract_plane(t_scene *scene, char **content, int i)
{
	char	*content_str;
	char	**cont_arr;

	content_str = find_content_str(content, "pl"); //fix later
	cont_arr = ft_split(content_str, ' ');
	ft_memset(content_str, 0, ft_strlen(content_str));
	if (!cont_arr)
		return (EXIT_FAILURE);
	if (cont_arr[4])
		return (ft_strarray_free(cont_arr), extract_error(pl), EXIT_FAILURE);
	if (save_cords(scene, cont_arr[1], pl, i))
		return (ft_strarray_free(cont_arr), EXIT_FAILURE);
	if (save_vector(scene, cont_arr[2], pl, i))
		return (ft_strarray_free(cont_arr), EXIT_FAILURE);
	if (extract_rgb(&(scene->plane[i]->rgb), cont_arr[3]))
	{
		ft_strarray_free(cont_arr);
		return (extract_error(pl), EXIT_FAILURE);
	}
	return (ft_strarray_free(cont_arr), EXIT_SUCCESS);
}

int	extract_cylinder(t_scene *scene, char **content, int i)
{
	char	*content_str;
	char	**cont_arr;

	content_str = find_content_str(content, "cy"); //fix later
	cont_arr = ft_split(content_str, ' ');
	ft_memset(content_str, 0, ft_strlen(content_str));
	if (!cont_arr)
		return (EXIT_FAILURE);
	if (cont_arr[6])
		return (ft_strarray_free(cont_arr), extract_error(cyka), EXIT_FAILURE);
	if (save_cords(scene, cont_arr[1], cyka, i))
		return (ft_strarray_free(cont_arr), EXIT_FAILURE);
	if (save_vector(scene, cont_arr[2], cyka, i))
		return (ft_strarray_free(cont_arr), EXIT_FAILURE);
	scene->cylinder[i]->diameter = get_numbers(cont_arr[3], 1);
	if (scene->cylinder[i]->diameter > 1000.0F
		|| scene->cylinder[i]->diameter < -1000.0F) //idk about limits again
		return (ft_strarray_free(cont_arr), extract_error(cyka), EXIT_FAILURE);
	scene->cylinder[i]->height = get_numbers(cont_arr[4], 1);
	if (scene->cylinder[i]->height > 1000.0F
		|| scene->cylinder[i]->height < -1000.0F)
		return (ft_strarray_free(cont_arr), extract_error(cyka), EXIT_FAILURE);
	if (extract_rgb(&(scene->cylinder[i]->rgb), cont_arr[5]))
		return (ft_strarray_free(cont_arr), extract_error(cyka), EXIT_FAILURE);
	return (ft_strarray_free(cont_arr), EXIT_SUCCESS);
}
//maybe fix illegal returns idk