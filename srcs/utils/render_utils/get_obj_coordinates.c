//
// Created by jules on 31/08/2024.
//

#include <miniRT_render.h>

t_coordinates	get_obj_coordinates(void *obj, int obj_type)
{
	if (obj_type == sp)
		return (((t_sphere *)(obj))->center);
	if (obj_type == pl)
		return (((t_plane *)(obj))->coordinates);
	if (obj_type == cyka || obj_type == cyka_circle)
		return (((t_cylinder *)(obj))->center);
	return ((t_coordinates){0.f, 0.f, 0.f});
}
