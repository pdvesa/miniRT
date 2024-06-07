/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svesa <svesa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 16:52:37 by svesa             #+#    #+#             */
/*   Updated: 2024/06/07 16:07:59 by svesa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT_parsing.h>

t_scene	new_render_scene(void)
{
	t_scene	scene;

	scene.ambient_light = NULL;
	scene.camera = NULL;
	scene.cylinder = NULL;
	scene.plane = NULL;
	scene.sphere = NULL;
	return (scene);
}

void	free_render_scene(t_scene *scene)
{
	if (scene->ambient_light)
	{
		free(scene->ambient_light);
		scene->ambient_light = NULL; //need this to exit
	}
	if (scene->camera)
		free(scene->camera);
	if (scene->light)
		free(scene->light);
	if (scene->sphere)
		ft_free_array((void **)(scene->sphere));
	if (scene -> plane)
		ft_free_array((void **)(scene->plane));
	if (scene -> cylinder)
		ft_free_array((void **)(scene->cylinder));
}

void	parse_content(t_scene *scene, char **content, int *n_objs)
{
	if (parse_ambient(scene, content))
		free_render_scene(scene);
	else if (parse_camera(scene, content))
		free_render_scene(scene);
	else if (parse_light(scene, content))
		free_render_scene(scene);
	else if ((parse_sphere(scene, content, n_objs[3])))
		free_render_scene(scene);
	else if ((parse_plane(scene, content, n_objs[4])))
		free_render_scene(scene);
	else if ((parse_cylinder(scene, content, n_objs[5])))
		free_render_scene(scene);
}

t_scene	parse_file(char *filename)
{
	t_scene			scene;
	int				n_objs[6];
	char			**content;

	scene = new_render_scene();
	content = read_file(filename);
	if (!content)
		return (scene);
	ft_memset(n_objs, 0, 6 * sizeof (int));
	if (valid_category(content, n_objs))
		parse_content(&scene, content, n_objs);
	ft_strarray_free(content);
	return (scene);
}
