//
// Created by jules on 08/06/2024.
//

#include <render_inter.h>

t_vector	normal_inter_sphere(t_ray *ray)
{
	t_vector	result;

	return (result);
}

t_vector	normal_inter_plane(t_ray *ray)
{
	t_vector		result;
	t_plane			*plane;
	t_coordinates	p1;
	t_coordinates	p2;

	plane = (t_plane *) ray->inter_point.object;
	p1 = translate_point(plane->coordinates, orthogonal_vector(plane->vector, 1, 0));
	p2 = translate_point(plane->coordinates, orthogonal_vector(plane->vector, 0, 1));
	result = cross_product(vector_from_points(p1, plane->coordinates),
					vector_from_points(p2, plane->coordinates));
	result = normalize_vector(result);
	return (result);
}

t_vector	normal_inter_cyka(t_ray *ray)
{
	t_vector	result;

	return (result);
}

t_vector	get_normal_to_inter(t_ray *ray)
{
	if (ray->inter_point.object_type == sp)
		return (normal_inter_sphere(ray));
	else if (ray->inter_point.object_type == pl)
		return (normal_inter_plane(ray));
	else
		return (normal_inter_cyka(ray));
}
