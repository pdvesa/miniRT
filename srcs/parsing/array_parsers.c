/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   array_parsers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svesa <svesa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 21:33:52 by svesa             #+#    #+#             */
/*   Updated: 2024/06/06 21:34:58 by svesa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT_parsing.h>

int	extract_sphere(t_scene *scene, char **content, int i) 
{
	char	*content_str;
	char	**content_array;
	
	content_str = find_content_str(content, 's'); //fix later
	content_array = ft_split(content_str, ' ');
	ft_memset(content_str, 0, ft_strlen(content_str));
	if (!content_array)
		return (EXIT_FAILURE);
	if (save_cords(scene, content_array[1], sp, i))
		return (ft_strarray_free(content_array), EXIT_FAILURE);
	scene->sphere[i]->diameter = get_numbers(content_array[2], 1);
	if (scene->sphere[i]->diameter < -100.0F || scene->ambient_light->ratio > 100.0F) //no idea about limit
		return (ft_strarray_free(content_array), extract_error(sp), EXIT_FAILURE); 
	if (extract_rgb(&(scene->sphere[i]->rgb), content_array[3]))
	{
		ft_strarray_free(content_array);
		return (extract_error(sp), EXIT_SUCCESS);
	}
	return (ft_strarray_free(content_array), EXIT_SUCCESS);
}

int	parse_sphere(t_scene *scene, char **content, int n_objs)
{
	int i;

	scene->sphere = ft_calloc(n_objs + 1, sizeof(t_sphere *));
	if (!(scene->sphere))
		return (EXIT_FAILURE);
	i = 0;
	while(i < n_objs)
	{
		scene->sphere[i] = ft_calloc(1, sizeof(t_sphere));
		if (!(scene->sphere[i]))
			return(EXIT_FAILURE); //free head and before here
		if (extract_sphere(scene, content, i))
			return(EXIT_FAILURE);
		i++;
	}
	scene->sphere[i] = NULL;
	return (EXIT_SUCCESS);
}

int	extract_plane(t_scene *scene, char **content, int i) 
{
	char	*content_str;
	char	**content_array;
	
	content_str = find_content_str(content, 'p'); //fix later
	content_array = ft_split(content_str, ' ');
	ft_memset(content_str, 0, ft_strlen(content_str));
	if (!content_array)
		return (EXIT_FAILURE);
	if (save_cords(scene, content_array[1], pl, i))
		return (ft_strarray_free(content_array), EXIT_FAILURE);
	if (save_vector(scene, content_array[2], pl, i))
		return (ft_strarray_free(content_array), EXIT_FAILURE);
	if (extract_rgb(&(scene->plane[i]->rgb), content_array[3]))
	{
		ft_strarray_free(content_array);
		return (extract_error(pl), EXIT_FAILURE);
	}
	return (ft_strarray_free(content_array), EXIT_SUCCESS);
}

int	parse_plane(t_scene *scene, char **content, int n_objs)
{
	int	i;
	
	scene->plane = ft_calloc(n_objs + 1, sizeof(t_plane *));
	if (!(scene->plane))
		return (EXIT_FAILURE);
	i = 0;
	while (i < n_objs)
	{
		scene->plane[i] = ft_calloc(1, sizeof(t_plane));
		if (!(scene->plane[i]))
			return (EXIT_FAILURE);
		if (extract_plane(scene, content, i))
			return (EXIT_FAILURE);
		i++;
	}
	scene->plane[i] = NULL;
	return (EXIT_SUCCESS);
}

int	extract_cylinder(t_scene *scene, char **content, int i) 
{
	char	*content_str;
	char	**content_array;
	
	content_str = find_content_str(content, 'c'); //fix later
	content_array = ft_split(content_str, ' ');
	ft_memset(content_str, 0, ft_strlen(content_str));
	if (!content_array)
		return (EXIT_FAILURE);
	if (save_cords(scene, content_array[1], cyka, i))
		return (ft_strarray_free(content_array), EXIT_FAILURE);
	if (save_vector(scene, content_array[2], cyka, i))
		return (ft_strarray_free(content_array), EXIT_FAILURE);
	scene->cylinder[i]->diameter = get_numbers(content_array[3], 1);
	if (scene->cylinder[i]->diameter > 1000.0F || scene->cylinder[i]->diameter < -1000.0F) //idk about limits again
		return (ft_strarray_free(content_array), extract_error(cyka), EXIT_FAILURE);
	scene->cylinder[i]->height = get_numbers(content_array[4], 1);
	if (scene->cylinder[i]->height > 1000.0F || scene->cylinder[i]->height < -1000.0F)
		return (ft_strarray_free(content_array), extract_error(cyka), EXIT_FAILURE);
	if (extract_rgb(&(scene->cylinder[i]->rgb), content_array[5]))
	{
		ft_strarray_free(content_array);
		return (extract_error(cyka), EXIT_FAILURE);
	}
	return (ft_strarray_free(content_array), EXIT_SUCCESS);
}

int	parse_cylinder(t_scene *scene, char **content, int n_objs)
{
	int	i;
	
	scene->cylinder = ft_calloc(n_objs + 1, sizeof(t_cylinder *));
	if (!(scene->cylinder))
		return (EXIT_FAILURE);
	i = 0;
	while (i < n_objs)
	{
		scene->cylinder[i] = ft_calloc(1, sizeof(t_cylinder));
		if (!(scene->cylinder[i]))
			return (EXIT_FAILURE);
		if (extract_cylinder(scene, content, i))
			return (EXIT_FAILURE);
		i++;
	}
	scene->cylinder[i] = NULL;
	return (EXIT_SUCCESS);
}