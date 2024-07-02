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

	inter.object = NULL;
	cam_to_center = vector_from_points(line->origin, sphere->center);
	roots = poly_root(dot_product(line->direction, line->direction),
					  2.0f * dot_product(line->direction, cam_to_center),
					  dot_product(cam_to_center, cam_to_center) -
					  powf(sphere->diameter / 2, 2));
	line_len = inter_root_linelen(roots);
	if (line_len < 0.0f)
		return (inter);
	inter.object_type = sp;
	inter.object = sphere;
	inter.coordinates = translate_point(line->origin, scalar_vector(line_len, line->direction));
	return (inter);
}
