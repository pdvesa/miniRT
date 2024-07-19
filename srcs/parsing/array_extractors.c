/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_extractors.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svesa <svesa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 15:58:09 by svesa             #+#    #+#             */
/*   Updated: 2024/06/18 19:22:56 by svesa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT_parsing.h>

int	extract_sphere(t_scene *scene, char **content, int i)
{
	char	*content_str;
	char	**cont_arr;

	content_str = find_content_str(content, "sp");
	cont_arr = ft_split(content_str, ' ');
	ft_memset(content_str, 0, ft_strlen(content_str));
	if (!cont_arr)
		return (EXIT_FAILURE);
	if (ft_strarray_len(cont_arr) != 4)
		return (erreur_dictateur(cont_arr, sp));
	if (save_cords(scene, cont_arr[1], sp, i))
		return (erreur_dictateur(cont_arr, sp));
	scene->sphere[i]->diameter = get_numbers(cont_arr[2], 1);
	if (scene->sphere[i]->diameter < 0.0F
		|| scene->sphere[i]->diameter > (float)ARBITARY_LIMIT)
		return (erreur_dictateur(cont_arr, sp));
	if (extract_rgb(&(scene->sphere[i]->rgb), cont_arr[3]))
		return (erreur_dictateur(cont_arr, sp));
	return (ft_strarray_free(cont_arr), EXIT_SUCCESS);
}

int	extract_plane(t_scene *scene, char **content, int i)
{
	char	*content_str;
	char	**cont_arr;

	content_str = find_content_str(content, "pl");
	cont_arr = ft_split(content_str, ' ');
	ft_memset(content_str, 0, ft_strlen(content_str));
	if (!cont_arr)
		return (EXIT_FAILURE);
	if (ft_strarray_len(cont_arr) != 4)
		return (erreur_dictateur(cont_arr, pl));
	if (save_cords(scene, cont_arr[1], pl, i))
		return (erreur_dictateur(cont_arr, pl));
	if (extract_vector(&(scene->plane[i]->vector), cont_arr[2]))
		return (erreur_dictateur(cont_arr, pl));
	if (extract_rgb(&(scene->plane[i]->rgb), cont_arr[3]))
		return (erreur_dictateur(cont_arr, pl));
	return (ft_strarray_free(cont_arr), EXIT_SUCCESS);
}

int	extract_cylinder(t_scene *scene, char **content, int i)
{
	char	*content_str;
	char	**cont_arr;

	content_str = find_content_str(content, "cy");
	cont_arr = ft_split(content_str, ' ');
	ft_memset(content_str, 0, ft_strlen(content_str));
	if (!cont_arr)
		return (EXIT_FAILURE);
	if (ft_strarray_len(cont_arr) != 6)
		return (erreur_dictateur(cont_arr, cyka));
	if (save_cords(scene, cont_arr[1], cyka, i))
		return (erreur_dictateur(cont_arr, cyka));
	if (extract_vector(&(scene->cylinder[i]->vector), cont_arr[2]))
		return (erreur_dictateur(cont_arr, cyka));
	scene->cylinder[i]->diameter = get_numbers(cont_arr[3], 1);
	if (scene->cylinder[i]->diameter > (float)ARBITARY_LIMIT
		|| scene->cylinder[i]->diameter < 0.0F)
		return (erreur_dictateur(cont_arr, cyka));
	scene->cylinder[i]->height = get_numbers(cont_arr[4], 1);
	if (scene->cylinder[i]->height > (float)ARBITARY_LIMIT
		|| scene->cylinder[i]->height < 0.0F)
		return (erreur_dictateur(cont_arr, cyka));
	if (extract_rgb(&(scene->cylinder[i]->rgb), cont_arr[5]))
		return (erreur_dictateur(cont_arr, cyka));
	return (ft_strarray_free(cont_arr), EXIT_SUCCESS);
}
