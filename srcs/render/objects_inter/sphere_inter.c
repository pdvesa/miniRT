//
// Created by jules on 11/06/2024.
//

#include <miniRT_render.h>

t_inter_point	sphere_inter(t_line *line, t_sphere *sphere)
{
	t_inter_point	inter;
	t_polyroot		roots;
	float			line_len;
	t_vector		cam_to_center;

	inter.coordinates = new_far_point();
	inter.object_type = sp;
	inter.object = sphere;
	cam_to_center = vector_from_points(line->origin, sphere->center);
	roots = poly_root(dot_product(line->direction, line->direction),
					  dot_product(scalar_vector(2.0f, line->direction), cam_to_center),
					  (dot_product(cam_to_center, cam_to_center) -
					   powf(sphere->diameter / 2, 2)));
	if (roots.n == 0)
		return (inter);
	else if (roots.n == 1)
		line_len = roots.values[0];
	else
	{
		if (roots.values[0] > roots.values[1])
			line_len = roots.values[1];
		else
			line_len = roots.values[0];
	}
	inter.coordinates = translate_point(line->origin, scalar_vector(line_len, line->direction));
	return (inter);
}
