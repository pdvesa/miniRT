//
// Created by jules on 11/06/2024.
//

#include <render_inter.h>

t_inter_point	plane_inter(t_line *line, t_plane *plan)
{
	t_inter_point	inter;
	float			line_len;
	float			dot;

	inter.coordinates = new_far_point();
	inter.object_type = pl;
	inter.object = plan;
	dot = dot_product(plan->vector, line->direction);
	if (dot <= 0)
		return (inter);
	line_len = dot_product(plan->vector, vector_from_points(plan->coordinates, line->origin)) / dot;
	inter.coordinates = translate_point(line->origin, scalar_vector(line_len, line->direction));
	return (inter);
}
