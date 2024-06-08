//
// Created by jules on 08/06/2024.
//

#include <miniRT_render.h>

t_vector	normal_inter_sphere(t_ray *ray)
{
	t_vector result;

	return (result);
}

t_vector	normal_inter_plane(t_ray *ray)
{
	t_vector result;

	return (result);
}

t_vector	normal_inter_cyka(t_ray *ray)
{
	t_vector result;

	return (result);
}

t_vector	calculate_normal_inter(t_ray *ray)
{
	if (ray->inter_point.object_type == sp)
		return (normal_inter_sphere(ray));
	else if (ray->inter_point.object_type == pl)
		return (normal_inter_plane(ray));
	else
		return (normal_inter_cyka(ray));
}
