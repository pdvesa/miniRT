/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svesa <svesa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 16:52:37 by svesa             #+#    #+#             */
/*   Updated: 2024/06/05 20:41:24 by svesa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT_parsing.h>

t_scene	new_render_scene()
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
	if (scene -> ambient_light)
		free(scene -> ambient_light);
	if (scene -> camera)
		free(scene -> camera);
	if (scene -> light)
		free(scene -> light);
	if (scene -> sphere)
		ft_free_array((void**)(scene -> sphere));
	if (scene -> plane)
		ft_free_array((void**)(scene -> plane));
	if (scene -> cylinder)
		ft_free_array((void**)(scene -> cylinder));
}


void parse_content(t_scene *scene, char **content, int *n_objs)
{
	if (scene_parser(scene, content, n_objs, A))
		return ;
	else if (scene_parser(scene, content, n_objs, C))
		free_render_scene(scene);
	else if (scene_parser(scene, content, n_objs, L))
		free_render_scene(scene);
	// else if (scene_parser(scene, content, n_objs, sp))
	// 	free_render_scene(scene);
	// else if (scene_parser(scene, content, n_objs, pl))
	// 	free_render_scene(scene);
	// else if (scene_parser(scene, content, n_objs, cyka))
	// 	free_render_scene(scene);
}


t_scene	parse_file(char *filename)
{
	t_scene			scene;
	int 			n_objs[6];
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
