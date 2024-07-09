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

t_vector	normal_inter_cyka_plane(t_ray *ray)
{
	t_plane			circles[2];
	t_inter_point	inter;

	get_cyka_circles_planes(ray->inter_point.object, circles);
	inter = plane_inter(&ray->line, &circles[0]);
	if (point_equals(inter.coordinates, ray->inter_point.coordinates))
		return (circles[0].vector);
	return (circles[1].vector);
}

t_vector	normal_inter_cyka(t_ray *ray)
{
	t_vector		result;
	t_vector		var;
	t_cylinder		*cylinder;

	if (ray->inter_point.object_type == cyka_circle)
		return (normal_inter_cyka_plane(ray));
	cylinder = (t_cylinder*) ray->inter_point.object;
	var = scalar_vector(dot_product(
			vector_from_points(ray->inter_point.coordinates, cylinder->center),
			cylinder->vector), cylinder->vector);
	result = vector_from_points(ray->inter_point.coordinates
			,translate_point(cylinder->center, var)); //TODO CHECK
	result = normalize_vector(result);
	return (result);
}

t_vector	get_normal_to_inter(t_ray *ray)
{
	if (ray->inter_point.object_type == sp)
		return (normal_inter_sphere(ray));
	else if (ray->inter_point.object_type == pl)
		return (((t_plane *)ray->inter_point.object)->vector);
	else
		return (normal_inter_cyka(ray));
}
