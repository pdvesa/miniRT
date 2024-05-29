//
// Created by Jules Cayot on 13/05/2024.
//

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

t_scene	free_render_scene(t_scene *scene)
{
	if (scene -> ambient_light)
		ft_free_array(scene -> ambient_light);
	if (scene -> camera)
		ft_free_array(scene -> camera);
	if (scene -> light)
		ft_free_array(scene -> light);
	if (scene -> sphere)
		ft_free_array(scene -> sphere);
	if (scene -> plane)
		ft_free_array(scene -> plane);
	if (scene -> cylinder)
		ft_free_array(scene -> cylinder);
}

void parse_content(t_scene *scene, char **content, int *n_objs)
{
	if (!scene_parser(scene, content, n_objs, A))
		return ;
	else if (!scene_parser(scene, content, n_objs, C))
		free_render_scene(scene);
	else if (!scene_parser(scene, content, n_objs, L))
		free_render_scene(scene);
	else if (!scene_parser(scene, content, n_objs, sp))
		free_render_scene(scene);
	else if (!scene_parser(scene, content, n_objs, pl))
		free_render_scene(scene);
	else if (!scene_parser(scene, content, n_objs, cyka))
		free_render_scene(scene);
}

t_scene	parse_file(char *filename)
{
	t_scene	scene;
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
