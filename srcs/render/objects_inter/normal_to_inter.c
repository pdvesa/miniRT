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
	float			vertical_distance;
	t_cylinder		*cylinder;

	cylinder = (t_cylinder*) ray->inter.object;
	vertical_distance = sqrtf(powf(point_distance(ray->inter.point,
		cylinder->center), 2.f) - powf(cylinder->diameter / 2.f, 2.f));
	if (dot_product(cylinder->vector,
		vector_from_points(cylinder->center, ray->inter.point)) < 0.f)
		vertical_distance *=-1.f;
	result = vector_from_points(translate_point(cylinder->center,
		scalar_vec(vertical_distance, cylinder->vector)), ray->inter.point);
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
