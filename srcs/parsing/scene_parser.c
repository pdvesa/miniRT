/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svesa <svesa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 11:16:09 by svesa             #+#    #+#             */
/*   Updated: 2024/06/18 19:45:16 by svesa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT_parsing.h>

int	parse_ambient(t_scene *scene, char **content)
{
	char	*content_str;
	char	**cont_arr;

	scene->ambient_light = ft_calloc(1, sizeof(t_ambient_light));
	if (!(scene->ambient_light))
		return (EXIT_FAILURE);
	content_str = find_content_str(content, "A");
	cont_arr = ft_split(content_str, ' ');
	if (!cont_arr)
		return (EXIT_FAILURE);
	if (ft_strarray_len(cont_arr) != 3)
		return (ft_strarray_free(cont_arr), extract_error(A), EXIT_FAILURE);
	scene->ambient_light->ratio = get_numbers(cont_arr[1], 1);
	if (scene->ambient_light->ratio < 0.0F
		|| scene->ambient_light->ratio > 1.0F)
		return (ft_strarray_free(cont_arr), extract_error(A), EXIT_FAILURE); //fix for norm, now i was lazy
	if (extract_rgb(&(scene->ambient_light->rgb), cont_arr[2]))
	{
		ft_strarray_free(cont_arr);
		return (extract_error(A), EXIT_FAILURE);
	}
	return (ft_strarray_free(cont_arr), EXIT_SUCCESS);
}

int	parse_camera(t_scene *scene, char **content)
{
	char	*content_str;
	char	**cont_arr;

	scene->camera = ft_calloc(1, sizeof(t_camera));
	if (!(scene->camera))
		return (EXIT_FAILURE);
	content_str = find_content_str(content, "C");
	cont_arr = ft_split(content_str, ' ');
	if (!cont_arr)
		return (EXIT_FAILURE);
	if (ft_strarray_len(cont_arr) != 4)
		return (ft_strarray_free(cont_arr), extract_error(C), EXIT_FAILURE);
	if (save_cords(scene, cont_arr[1], C, 0))
		return (ft_strarray_free(cont_arr), EXIT_FAILURE);
	if (save_vector(scene, cont_arr[2], C, 0))
		return (ft_strarray_free(cont_arr), EXIT_FAILURE);
	scene->camera->fov = get_numbers(cont_arr[3], 0);
	if (scene->camera->fov > 180 || scene->camera->fov < 0)
		return (ft_strarray_free(cont_arr), extract_error(C), EXIT_FAILURE);
	return (ft_strarray_free(cont_arr), EXIT_SUCCESS);
}

int	parse_light(t_scene *scene, char **content)
{
	char	*content_str;
	char	**cont_arr;

	scene->light = ft_calloc(1, sizeof(t_light));
	if (!(scene->light))
		return (EXIT_FAILURE);
	content_str = find_content_str(content, "L");
	cont_arr = ft_split(content_str, ' ');
	if (!cont_arr)
		return (EXIT_FAILURE);
	if (ft_strarray_len(cont_arr) != 3)
		return (ft_strarray_free(cont_arr), extract_error(L), EXIT_FAILURE);
	if (save_cords(scene, cont_arr[1], L, 0))
		return (ft_strarray_free(cont_arr), EXIT_FAILURE);
	scene->light->brightness = get_numbers(cont_arr[2], 1);
	if (scene->light->brightness > 1.0F || scene->light->brightness < 0.0F)
		return (ft_strarray_free(cont_arr), extract_error(L), EXIT_FAILURE);
	return (ft_strarray_free(cont_arr), EXIT_SUCCESS);
}

int	parse_sphere(t_scene *scene, char **content, int n_objs)
{
	int	i;

	scene->sphere = ft_calloc(n_objs + 1, sizeof(t_sphere *));
	if (!(scene->sphere))
		return (EXIT_FAILURE);
	i = 0;
	while (i < n_objs)
	{
		scene->sphere[i] = ft_calloc(1, sizeof(t_sphere));
		if (!(scene->sphere[i]))
			return (EXIT_FAILURE); //i think we free after error so no free here
		if (extract_sphere(scene, content, i))
			return (EXIT_FAILURE);
		i++;
	}
	scene->sphere[i] = NULL;
	return (EXIT_SUCCESS);
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

// rounding errors in floatoi, need fix
// check floats in general
// tabs are error rn, as subject didnt mention
// test with invalid file types permissions etc
// for now if multiple input field has . insted of , ie. vector 0.5.0.4.06 it will gracefully exit with no leaks but no error message, fix
//if (!scene.ambient_light)
//		return (1);

// int scene_parser(t_scene *scene, char **content, int *n_objs, int item)
// {	
// 	if (item == A)
// 		return (parse_ambient(scene, content));
// 	else if (item == C)
// 		return (parse_camera(scene, content));
// 	else if (item == L)
// 		return (parse_light(scene, content));
// 	else if (item == sp)
// 		return (parse_sphere(scene, content, n_objs[3]));
// 	else if (item == pl)
// 		return (parse_plane(scene, content, n_objs[4]));
// 	else if (item == cyka)
// 		return (parse_cylinder(scene, content, n_objs[5]));
// 	else 
// 		return (EXIT_FAILURE);
// }
