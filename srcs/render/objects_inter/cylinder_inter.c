//
// Created by jules on 11/06/2024.
//

#include <miniRT_render.h>

t_inter_point	cyka_circles_inter(t_line *line, t_cylinder *cylinder)
{
	t_inter_point	inter;
	t_inter_point	inter1;
	t_inter_point	inter2;
	t_plane			circles[2];

	inter.object = NULL;
	get_cyka_circles_planes(cylinder, circles);
	inter1 = plane_inter(line, &circles[0]);
	inter2 = plane_inter(line, &circles[1]);
	if (point_distance(inter1.coordinates, circles[0].coordinates) > cylinder->diameter / 2.0f)
		inter1.object = NULL;
	if (point_distance(inter2.coordinates, circles[1].coordinates) > cylinder->diameter / 2.0f)
		inter2.object = NULL;
	if (inter1.object || inter2.object)
	{
		inter.object = cylinder;
		inter.object_type = cyka_circle;
		if (!inter2.object || (inter1.object
			&& point_distance(inter1.coordinates, line->origin)
			< point_distance(inter2.coordinates, line->origin)))
			inter.coordinates = inter1.coordinates;
		else
			inter.coordinates = inter2.coordinates;
	}
	return (inter);
}

float	curve_line_len(t_line *line, t_cylinder *cylinder)
{
	t_polyroot		roots;
	t_vector		A;
	t_vector		B;

	A = substract_vector(line->direction,scalar_vector(
			dot_product(line->direction, cylinder->vector), cylinder->vector));
	B = substract_vector(vector_from_points(cylinder->center ,line->origin),
						 scalar_vector(dot_product(
								 vector_from_points(cylinder->center, line->origin),
								 cylinder->vector), cylinder->vector)); //TODO check vector from points
	roots = poly_root(dot_product(A, A), 2.0f * dot_product(A, B), dot_product(B, B) - powf(cylinder->diameter, 2.0f));
	return (inter_root_linelen(roots));
}

t_inter_point	cyka_curve_inter(t_line *line, t_cylinder *cylinder)
{
	t_inter_point	inter;
	float			line_len;

	inter.object = NULL;
	line_len = curve_line_len(line, cylinder);
	if (line_len < 0.0f)
		return (inter);
	inter.object_type = cyka;
	inter.object = cylinder;
	inter.coordinates = translate_point(line->origin, scalar_vector(line_len, line->direction));
	if (point_distance(cylinder->center, inter.coordinates) >
			sqrtf(powf(cylinder->height, 2.0f) + powf(cylinder->diameter / 2.0f, 2.0f)))
		inter.object = NULL;
	return (inter);
}

t_inter_point	cylinder_inter(t_line *line, t_cylinder *cylinder)
{
	t_inter_point	inter_cyka_part;
	t_inter_point	inter_circle_part;

	inter_cyka_part = cyka_curve_inter(line, cylinder);
	inter_circle_part = cyka_circles_inter(line, cylinder);
	if (inter_cyka_part.object || inter_circle_part.object)
	{
		if (!inter_cyka_part.object || (inter_circle_part.object &&
				point_distance(inter_circle_part.coordinates, line->origin)
				< point_distance(inter_cyka_part.coordinates, line->origin)))
			return (inter_circle_part);
		else
			return (inter_cyka_part);
	}
	return (inter_cyka_part);
}
