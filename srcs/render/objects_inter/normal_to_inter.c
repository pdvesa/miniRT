//
// Created by jules on 08/06/2024.
//

#include <miniRT_render.h>

t_vector	normal_inter_sphere(t_ray *ray)
{
	t_vector	result;

	result = vector_from_points(((t_sphere *) ray->inter_point.object)->center,
								ray->inter_point.coordinates);
	result = normalize_vector(result);
	return (result);
}

t_vector	normal_inter_cyka(t_ray *ray)
{
	t_vector		result;
	t_vector		var;
	t_cylinder		*cylinder;

	cylinder = (t_cylinder*) ray->inter_point.object;
	var = scalar_vector(dot_product(
		vector_from_points(ray->inter_point.coordinates, cylinder->center),
		cylinder->vector), cylinder->vector);
	result = vector_from_points(translate_point(cylinder->center, var),
		ray->inter_point.coordinates);
	result = normalize_vector(result);
	return (result);
}

t_vector	get_normal_to_inter(t_ray *ray)
{
	if (ray->inter_point.object_type == sp)
		return (normal_inter_sphere(ray));
	else if (ray->inter_point.object_type == pl)
		return (((t_plane *) ray->inter_point.object)->vector);
	else if (ray->inter_point.object_type == cyka_circle)
		return (((t_cylinder *) ray->inter_point.object)->vector);
	else
		return (normal_inter_cyka(ray));
}
