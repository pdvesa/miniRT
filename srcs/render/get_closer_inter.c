//
// Created by Jules Cayot on 5/20/24.
//

#include <miniRT_render.h>

t_coordinates new_far_point()
{
	t_coordinates	far_point;

	far_point.x = MAXFLOAT;
	far_point.y = MAXFLOAT;
	far_point.z = MAXFLOAT;
	return (far_point);
}

t_coordinates get_closer_inter(t_render_scene *scene, int cam_index, unsigned int w, unsigned int h)
{
	t_coordinates closer;
	t_coordinates competidor;

	closer = new_far_point();
	
}
