//
// Created by Jules Cayot on 13/05/2024.
//

#include <miniRT_parsing.h>

t_render_scene	new_render_scene()
{
	t_render_scene	scene;

	scene.ambient_light = NULL;
	scene.camera = NULL;
	scene.cylinder = NULL;
	scene.plane = NULL;
	scene.sphere = NULL;
	return (scene);
}

t_render_scene	free_render_scene(t_render_scene *scene)
{
	if (scene -> ambient_light)
		free(scene -> ambient_light);
	if (scene -> camera)
		free(scene -> camera);
	if (scene -> light)
		free(scene -> light);
	if (scene -> sphere)
		free(scene -> sphere);
	if (scene -> plane)
		free(scene -> plane);
	if (scene -> cylinder)
		free(scene -> cylinder);
}

void parse_content(t_render_scene *scene, char **content, int *n_objs)
{
	if (!scene_parser(scene -> ambient_light, content, n_objs, A))
		return ;
	else if (!scene_parser(scene -> camera, content, n_objs, C))
		free_render_scene(scene);
	else if (!scene_parser(scene -> light, content, n_objs, L))
		free_render_scene(scene);
	else if (!scene_parser(scene -> sphere, content, n_objs, sp))
		free_render_scene(scene);
	else if (!scene_parser(scene -> plane, content, n_objs, pl))
		free_render_scene(scene);
	else if (!scene_parser(scene -> cylinder, content, n_objs, cyka))
		free_render_scene(scene);
}

t_render_scene	parse_file(char *filename)
{
	t_render_scene	scene;
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
