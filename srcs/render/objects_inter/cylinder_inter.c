/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_inter.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcayot <jcayot.student@hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 20:56:16 by jcayot            #+#    #+#             */
/*   Updated: 2024/07/18 20:56:17 by jcayot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT_render.h>

t_inter	cyka_circles_inter(t_line *line, t_cylinder *cyl)
{
	t_inter	inter;
	t_inter	i1;
	t_inter	i2;
	t_plane	circles[2];

	inter.object = NULL;
	get_cyka_circles_planes(cyl, circles);
	i1 = plane_inter(line, &circles[0]);
	i2 = plane_inter(line, &circles[1]);
	if (!i1.object || point_distance(i1.point, circles[0].coordinates)
		> cyl->diameter / 2.0f)
		i1.object = NULL;
	if (!i2.object || point_distance(i2.point, circles[1].coordinates)
		> cyl->diameter / 2.0f)
		i2.object = NULL;
	if (!i1.object && !i2.object)
		return (inter);
	inter.object = cyl;
	inter.object_type = cyka_circle;
	if (!i2.object || (i1.object && point_distance(i1.point, line->origin)
			< point_distance(i2.point, line->origin)))
		inter.point = i1.point;
	else
		inter.point = i2.point;
	return (inter);
}

void	curve_line_lenghts(t_line *line, t_cylinder *cyl, float *result)
{
	float	cal1;
	float	cal2;
	float	cal3;

	result[0] = -1.f;
	result[1] = -1.f;
	cal3 = dot_product(cross_product(line->direction, cyl->vector),
			cross_product(line->direction, cyl->vector));
	if (cal3 == 0.f)
		return ;
	cal2 = sqrtf((cal3 * powf(cyl->diameter / 2.f, 2.f))
			- (dot_product(cyl->vector, cyl->vector) * powf(
					dot_product(vector_from_points(line->origin, cyl->center),
						cross_product(line->direction, cyl->vector)), 2.f)));
	if (cal2 < 0.f || isnanf(cal2))
		return ;
	cal1 = dot_product(cross_product(line->direction, cyl->vector),
			cross_product(vector_from_points(line->origin,
					cyl->center), cyl->vector));
	result[0] = (cal1 + cal2) / cal3;
	result[1] = (cal1 - cal2) / cal3;
}

t_inter	pick_curve_inter(t_line *l, t_inter i, t_cylinder *cyl, float *l_l)
{
	if (l_l[0] < l_l[1] && l_l[0] > FLOAT_MARGIN)
	{
		i.point = translate_point(l->origin, scalar_vec(l_l[0], l->direction));
		if (powf(point_distance(cyl->center, i.point), 2.0f) < powf(cyl->height
				/ 2.0f, 2.0f) + powf(cyl->diameter / 2.0f, 2.0f))
			return (i);
	}
	if (l_l[1] > FLOAT_MARGIN)
	{
		i.point = translate_point(l->origin, scalar_vec(l_l[1], l->direction));
		if (powf(point_distance(cyl->center, i.point), 2.0f) < powf(cyl->height
				/ 2.0f, 2.0f) + powf(cyl->diameter / 2.0f, 2.0f))
			return (i);
	}
	if (l_l[0] > FLOAT_MARGIN)
	{
		i.point = translate_point(l->origin, scalar_vec(l_l[0], l->direction));
		if (powf(point_distance(cyl->center, i.point), 2.0f) < powf(cyl->height
				/ 2.0f, 2.0f) + powf(cyl->diameter / 2.0f, 2.0f))
			return (i);
	}
	i.object = NULL;
	return (i);
}

t_inter	cyka_curve_inter(t_line *line, t_cylinder *cylinder)
{
	t_inter	inter;
	float	line_lenghts[2];

	inter.object = NULL;
	curve_line_lenghts(line, cylinder, line_lenghts);
	if (line_lenghts[0] < FLOAT_MARGIN && line_lenghts[1] < FLOAT_MARGIN)
		return (inter);
	inter.object_type = cyka;
	inter.object = cylinder;
	return (pick_curve_inter(line, inter, inter.object, line_lenghts));
}

t_inter	closer_cylinder_inter(t_line *line, t_cylinder *cylinder)
{
	t_inter	inter_cyka_part;
	t_inter	inter_circle_part;

	inter_cyka_part = cyka_curve_inter(line, cylinder);
	inter_circle_part = cyka_circles_inter(line, cylinder);
	if (inter_cyka_part.object || inter_circle_part.object)
	{
		if (!inter_cyka_part.object || (inter_circle_part.object
				&& point_distance(inter_circle_part.point, line->origin)
				< point_distance(inter_cyka_part.point, line->origin)))
			return (inter_circle_part);
		return (inter_cyka_part);
	}
	return (inter_cyka_part);
}
