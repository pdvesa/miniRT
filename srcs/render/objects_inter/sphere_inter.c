//
// Created by jules on 11/06/2024.
//

#include <miniRT_render.h>

t_polyroot	sphere_inters(t_line *line, t_sphere *sphere)
{
	t_polyroot		roots;
	t_vector		center_to_cam;

	center_to_cam = vector_from_points( sphere->center ,line->origin);
	roots = poly_root(dot_product(line->direction, line->direction),
					  2.0f * dot_product(line->direction, center_to_cam),
					  dot_product(center_to_cam, center_to_cam) -
					  powf(sphere->diameter / 2, 2));
	return (roots);
}

t_inter_point	closer_sphere_inter(t_line *line, t_sphere *sphere)
{
	t_inter_point	inter;
	t_polyroot		roots;
	float			line_len;

	inter.object = NULL;
	roots = sphere_inters(line, sphere);
	line_len = inter_root_linelen(roots);
	if (line_len < 0.f)
		return (inter);
	inter.object_type = sp;
	inter.object = sphere;
	inter.coordinates = translate_point(line->origin, scalar_vector(line_len, line->direction));
	return (inter);
}
