//
// Created by Jules Cayot on 5/20/24.
//

#include <ft_maths.h>

t_coordinates	sphere_inter(t_line line, t_sphere sphere)
{
	t_coordinates	inter;
	t_polyroot		roots;
	float			line_len;
	t_vector		cam_to_center;

	cam_to_center = vector_from_points(line.origin, sphere.center);
	roots = poly_root(dot_product(line.direction, line.direction),
						 dot_product(scalar_vector(2.0f, line.direction), cam_to_center),
						 (dot_product(cam_to_center, cam_to_center) -
						  powf(sphere.diameter, 2)));
	if (roots.n == 0)
		return (new_far_point());
	else if (roots.n == 1)
		line_len = roots.roots[0];
	else
	{
		if (roots.roots[0] > roots.roots[1])
			line_len = roots.roots[1];
		else
			line_len = roots.roots[0];
	}
	inter = translate_point(line.origin, scalar_vector(line_len, line.direction));
	return (inter);
}

t_coordinates	plane_inter(t_line line, t_plane plan)
{
	t_coordinates	inter;
	float			line_len;
	float			dot;

	dot = dot_product(plan.vector, line.direction);
	if (dot < 0)
		return (new_far_point());
	else if (dot == 0)
		return (?????);
	inter = dot_product(plan.vector, vector_from_points(plan.coordinates, line.origin)) / dot;
	return (inter);
}
