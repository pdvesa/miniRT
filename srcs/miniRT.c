//
// Created by Jules Cayot on 13/05/2024.
//

#include "miniRT.h"

int	miniRT(char *filename)
{
	t_render_scene	scene;

	scene = parse_file(filename);
	if (!scene.camera)
		return (1);
}

int	main(int n, char *args[])
{
	if (n != 2)
		return (1);
	return (miniRT(args[1]));
}
