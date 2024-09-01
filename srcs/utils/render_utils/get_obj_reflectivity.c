//
// Created by jules on 31/08/2024.
//

#include <miniRT_render.h>

float	get_obj_reflectivity(void *obj, int obj_type)
{
	return (0.1f);
	if (obj_type == sp)
		return (((t_sphere *)(obj))->reflectivity);
	if (obj_type == pl)
		return (((t_plane *)(obj))->reflectivity);
	if (obj_type == cyka || obj_type == cyka_circle)
		return (((t_cylinder *)(obj))->reflectivity);
	return (0.f);
}
