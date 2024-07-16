//
// Created by jules on 11/06/2024.
//

#include <miniRT_render.h>

float	sphere_inter_line_len(t_line *line, t_sphere *sphere)
{
	t_polyroot		roots;
	t_vector		center_to_cam;

	center_to_cam = vector_from_points( sphere->center ,line->origin);
	roots = poly_root(dot_product(line->direction, line->direction),
					  2.0f * dot_product(line->direction, center_to_cam),
					  dot_product(center_to_cam, center_to_cam) -
					  powf(sphere->diameter / 2, 2));
	if (roots.n == 0 || (roots.n == 1 && roots.values[0] < FLOAT_MARGIN)
		|| (roots.n == 2 && roots.values[0] < FLOAT_MARGIN && roots.values[1] < FLOAT_MARGIN))
		return (-1.0f);
	if (roots.n == 1)
		return (roots.values[0]);
	else
	{
		if (roots.values[0] > roots.values[1] && roots.values[1] > FLOAT_MARGIN)
			return (roots.values[1]);
		else
			return (roots.values[0]);
	}
}

t_inter_point	closer_sphere_inter(t_line *line, t_sphere *sphere)
{
	t_inter_point	inter;
	float			line_len;

	inter.object = NULL;
	line_len = sphere_inter_line_len(line, sphere);
	if (line_len < 0.f)
		return (inter);
	inter.object_type = sp;
	inter.object = sphere;
	inter.coordinates = translate_point(line->origin, scalar_vector(line_len, line->direction));
	return (inter);
}
