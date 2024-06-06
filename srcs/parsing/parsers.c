/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svesa <svesa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 20:27:34 by svesa             #+#    #+#             */
/*   Updated: 2024/06/06 21:35:47 by svesa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT_parsing.h>

int	parse_ambient(t_scene *scene, char **content) 
{
	char	*content_str;
	char	**content_array;
	
	scene->ambient_light = ft_calloc(1, sizeof(t_ambient_light));
	if (!(scene->ambient_light))
		return (EXIT_FAILURE);
	content_str = find_content_str(content, 'A');
	content_array = ft_split(content_str, ' ');
	if (!content_array)
		return (EXIT_FAILURE);
	scene->ambient_light->ratio = get_numbers(content_array[1], 1);
	if (scene->ambient_light->ratio < 0.0F || scene->ambient_light->ratio > 1.0F) 
		return (ft_strarray_free(content_array), extract_error(A), EXIT_FAILURE); //fix for norm, now i was lazy
	if (extract_rgb(&(scene->ambient_light->rgb), content_array[2]))
	{
		ft_strarray_free(content_array);
		return (extract_error(A), EXIT_FAILURE);
	}
	return (ft_strarray_free(content_array), EXIT_SUCCESS);
}


	// if (content_array[2][0])
	// 	return (ft_strarray_free(content_array), EXIT_FAILURE); 


int	parse_camera(t_scene *scene, char **content)
{
	char *content_str;
	char **content_array;

	scene->camera = ft_calloc(1, sizeof(t_camera));
	if (!(scene->camera))
		return (EXIT_FAILURE);
	content_str = find_content_str(content, 'C');
	content_array = ft_split(content_str, ' ');
	if (!content_array)
		return (EXIT_FAILURE); //check control flow if there are double free or not frees on others on error
	if (save_cords(scene, content_array[1], C, 0))
		return (ft_strarray_free(content_array), EXIT_FAILURE);
	if (save_vector(scene, content_array[2], C, 0)) //i think this works or my brain has damage free content arrays also on error
		return (ft_strarray_free(content_array), EXIT_FAILURE);
	scene->camera->fov = ft_atoi(content_array[3]);
	if (scene->camera->fov > 180 || scene->camera->fov < 0)
		return (ft_strarray_free(content_array), extract_error(C), EXIT_FAILURE); // there was a problem that i had free scene->camera but complaine for not being allocated
	return (ft_strarray_free(content_array),EXIT_SUCCESS);
}

int	parse_light(t_scene *scene, char **content) 
{
	char *content_str;
	char **content_array;
	
	scene->light = ft_calloc(1, sizeof(t_light));
	if (!(scene->light))
		return (EXIT_FAILURE);
	content_str = find_content_str(content, 'L');
	content_array = ft_split(content_str, ' ');
	if (!content_array)
		return (EXIT_FAILURE);
	if (save_cords(scene, content_array[1], L, 0))
		return (ft_strarray_free(content_array), EXIT_FAILURE);
	scene->light->brightness = get_numbers(content_array[2], 1);
	if (scene->light->brightness > 1.0F || scene->light->brightness < 0.0F)
		return (ft_strarray_free(content_array), extract_error(L), EXIT_FAILURE);
	return (ft_strarray_free(content_array), EXIT_SUCCESS);
}
