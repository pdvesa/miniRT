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
	if (!inter1.object || point_distance(inter1.coordinates, circles[0].coordinates) > cylinder->diameter / 2.0f)
		inter1.object = NULL;
	if (!inter2.object || point_distance(inter2.coordinates, circles[1].coordinates) > cylinder->diameter / 2.0f)
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
	float	line_len1;
	float	line_len2;
	float	cal1;
	float	cal2;
	float	cal3;

	cal3 = dot_product(cross_product(line->direction, cylinder->vector),
		cross_product(line->direction, cylinder->vector));
	if (cal3 == 0.f)
		return (-1.f);
	cal2 = sqrtf((cal3 * powf(cylinder->diameter / 2.f, 2.f)) -
		(dot_product(cylinder->vector, cylinder->vector) *
		powf(dot_product(coordinates_to_vector(cylinder->center),
		cross_product(line->direction, cylinder->vector)), 2.f)));
	if (cal2 < 0.f)
		return (-1.f);
	cal1 = dot_product(cross_product(line->direction, cylinder->vector),
		cross_product(coordinates_to_vector(cylinder->center), cylinder->vector));
	line_len1 = (cal1 + cal2) / cal3;
	line_len2 = (cal1 - cal2) / cal3;
	if (line_len1 < line_len2 && line_len1 > FLOAT_MARGIN)
		return (line_len1);
	if (line_len2 > FLOAT_MARGIN)
		return (line_len2);
	return (-1.f);
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
	if (powf(point_distance(cylinder->center, inter.coordinates), 2.0f) >
			powf(cylinder->height / 2.0f, 2.0f) + powf(cylinder->diameter / 2.0f, 2.0f))
		inter.object = NULL;
	return (inter);
}

t_inter_point	closer_cylinder_inter(t_line *line, t_cylinder *cylinder)
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
		return (inter_cyka_part);
	}
	return (inter_cyka_part);
}
