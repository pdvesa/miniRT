//
// Created by jules on 11/06/2024.
//

#include <miniRT_render.h>

t_inter	cyka_circles_inter(t_line *line, t_cylinder *cylinder)
{
	t_inter	inter;
	t_inter	inter1;
	t_inter	inter2;
	t_plane	circles[2];

	inter.object = NULL;
	get_cyka_circles_planes(cylinder, circles);
	inter1 = plane_inter(line, &circles[0]);
	inter2 = plane_inter(line, &circles[1]);
	if (!inter1.object || point_distance(inter1.point, circles[0].coordinates) > cylinder->diameter / 2.0f)
		inter1.object = NULL;
	if (!inter2.object || point_distance(inter2.point, circles[1].coordinates) > cylinder->diameter / 2.0f)
		inter2.object = NULL;
	if (inter1.object || inter2.object)
	{
		inter.object = cylinder;
		inter.object_type = cyka_circle;
		if (!inter2.object || (inter1.object
			&& point_distance(inter1.point, line->origin)
			< point_distance(inter2.point, line->origin)))
			inter.point = inter1.point;
		else
			inter.point = inter2.point;
	}
	return (inter);
}

void	curve_line_lenghts(t_line *line, t_cylinder *cylinder, float *result)
{
	float	cal1;
	float	cal2;
	float	cal3;

	result[0] = -1.f;
	result[1] = -1.f;
	cal3 = dot_product(cross_product(line->direction, cylinder->vector),
		cross_product(line->direction, cylinder->vector));
	if (cal3 == 0.f)
		return ;
	cal2 = sqrtf((cal3 * powf(cylinder->diameter / 2.f, 2.f)) -
		(dot_product(cylinder->vector, cylinder->vector) *
		powf(dot_product(vector_from_points(line->origin, cylinder->center),
		cross_product(line->direction, cylinder->vector)), 2.f)));
	if (cal2 < 0.f || isnanf(cal2))
		return ;
	cal1 = dot_product(cross_product(line->direction, cylinder->vector),
		cross_product(vector_from_points(line->origin, cylinder->center), cylinder->vector));
	result[0] = (cal1 + cal2) / cal3;
	result[1] = (cal1 - cal2) / cal3;
}

t_inter	pick_curve_inter(t_line *l, t_inter inter, float *l_lens)
{
	t_cylinder	*cyl;

	cyl = (t_cylinder *) inter.object;
	if (l_lens[0] < l_lens[1] && l_lens[0] > FLOAT_MARGIN)
	{
		inter.point = translate_point(l->origin, scalar_vec(l_lens[0], l->direction));
		if (powf(point_distance(cyl->center, inter.point), 2.0f) <
				powf(cyl->height / 2.0f, 2.0f) + powf(cyl->diameter / 2.0f, 2.0f))
			return (inter);
	}
	if (l_lens[1] > FLOAT_MARGIN)
	{
		inter.point = translate_point(l->origin, scalar_vec(l_lens[1], l->direction));
		if (powf(point_distance(cyl->center, inter.point), 2.0f) <
				powf(cyl->height / 2.0f, 2.0f) + powf(cyl->diameter / 2.0f, 2.0f))
			return (inter);
	}
	if (l_lens[0] > FLOAT_MARGIN) {
		inter.point = translate_point(l->origin, scalar_vec(l_lens[0], l->direction));
		if (powf(point_distance(cyl->center, inter.point), 2.0f) <
				powf(cyl->height / 2.0f, 2.0f) + powf(cyl->diameter / 2.0f, 2.0f))
			return (inter);
	}
	inter.object = NULL;
	return (inter);
}

t_inter	cyka_curve_inter(t_line *line, t_cylinder *cylinder)
{
	t_inter	inter;
	float			line_lenghts[2];

	inter.object = NULL;
	curve_line_lenghts(line, cylinder, line_lenghts);
	if (line_lenghts[0] < FLOAT_MARGIN && line_lenghts[1] < FLOAT_MARGIN)
		return (inter);
	inter.object_type = cyka;
	inter.object = cylinder;
	return (pick_curve_inter(line, inter, line_lenghts));

}

t_inter	closer_cylinder_inter(t_line *line, t_cylinder *cylinder)
{
	t_inter	inter_cyka_part;
	t_inter	inter_circle_part;

	inter_cyka_part = cyka_curve_inter(line, cylinder);
	inter_circle_part = cyka_circles_inter(line, cylinder);
	if (inter_cyka_part.object || inter_circle_part.object)
	{
		if (!inter_cyka_part.object || (inter_circle_part.object &&
				point_distance(inter_circle_part.point, line->origin)
				< point_distance(inter_cyka_part.point, line->origin)))
			return (inter_circle_part);
		return (inter_cyka_part);
	}
	return (inter_cyka_part);
}
