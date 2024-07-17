//
// Created by jules on 08/06/2024.
//

#include <miniRT_render.h>

t_vector	normal_inter_sphere(t_ray *ray)
{
	t_vector	result;

	result = vector_from_points(((t_sphere *) ray->inter.object)->center,
								ray->inter.point);
	result = normalize_vector(result);
	return (result);
}

t_vector	normal_inter_cyka(t_ray *ray)
{
	t_vector		result;
	t_vector		var;
	t_cylinder		*cylinder;

	cylinder = (t_cylinder*) ray->inter.object;
	var = scalar_vec(dot_product(
		vector_from_points(ray->inter.point, cylinder->center),
		cylinder->vector), cylinder->vector);
	result = vector_from_points(translate_point(cylinder->center, var),
		ray->inter.point);
	result = normalize_vector(result);
	return (result);
}

t_vector	get_normal_to_inter(t_ray *ray)
{
	t_vector	normal;

	if (ray->inter.object_type == sp)
		return (normal_inter_sphere(ray));
	if (ray->inter.object_type == cyka)
		return (normal_inter_cyka(ray));
	if (ray->inter.object_type == pl)
		normal = ((t_plane *) ray->inter.object)->vector;
	else
		normal = ((t_cylinder *) ray->inter.object)->vector;
	return (normal);
}
