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

	scene->am_light = ft_calloc(1, sizeof(t_ambient_light));
	if (!(scene->am_light))
		return (EXIT_FAILURE);
	content_str = find_content_str(content, "A");
	cont_arr = ft_split(content_str, ' ');
	if (!cont_arr)
		return (EXIT_FAILURE);
	if (ft_strarray_len(cont_arr) != 3)
		return (erreur_dictateur(cont_arr, A));
	scene->am_light->ratio = get_numbers(cont_arr[1], 1);
	if (scene->am_light->ratio < 0.0F
		|| scene->am_light->ratio > 1.0F)
		return (erreur_dictateur(cont_arr, A));
	if (extract_rgb(&(scene->am_light->rgb), cont_arr[2]))
		return (erreur_dictateur(cont_arr, A));
	return (ft_strarray_free(cont_arr), EXIT_SUCCESS);
}

int	parse_camera(t_scene *scene, char **content)
{
	char	*content_str;
	char	**cont_arr;

	scene->cam = ft_calloc(1, sizeof(t_camera));
	if (!(scene->cam))
		return (EXIT_FAILURE);
	content_str = find_content_str(content, "C");
	cont_arr = ft_split(content_str, ' ');
	if (!cont_arr)
		return (EXIT_FAILURE);
	if (ft_strarray_len(cont_arr) != 4)
		return (erreur_dictateur(cont_arr, C));
	if (save_cords(scene, cont_arr[1], C, 0))
		return (erreur_dictateur(cont_arr, C));
	if (extract_vector(&(scene->cam->vect), cont_arr[2]))
		return (erreur_dictateur(cont_arr, C));
	scene->cam->fov = get_numbers(cont_arr[3], 0);
	if (scene->cam->fov > 179 || scene->cam->fov < 0)
		return (erreur_dictateur(cont_arr, C));
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
		return (erreur_dictateur(cont_arr, L));
	if (save_cords(scene, cont_arr[1], L, 0))
		return (erreur_dictateur(cont_arr, L));
	scene->light->brightness = get_numbers(cont_arr[2], 1);
	if (scene->light->brightness > 1.0F || scene->light->brightness < 0.0F)
		return (erreur_dictateur(cont_arr, L));
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
			return (EXIT_FAILURE);
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
