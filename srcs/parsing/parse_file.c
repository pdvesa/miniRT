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

t_render_scene	parse_file(char *filename)
{
	t_render_scene	scene;
	char			*content;

	scene = new_render_scene();
	content = read_file(filename);
	if (!content)
		return (scene);
	if (valid_category(content))
	{

	}
	free(content);
	return (scene);
}
