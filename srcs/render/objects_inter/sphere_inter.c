/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere_inter.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcayot <jcayot.student@hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 20:35:34 by jcayot            #+#    #+#             */
/*   Updated: 2024/07/18 20:35:36 by jcayot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT_render.h>

float	sphere_inter_line_len(t_line *line, t_sphere *sphere)
{
	t_polyroot		r;
	t_vector		center_to_cam;

	center_to_cam = vector_from_points(sphere->center, line->origin);
	r = poly_root(dot_product(line->direction, line->direction),
			2.0f * dot_product(line->direction, center_to_cam),
			dot_product(center_to_cam, center_to_cam)
			- powf(sphere->diameter / 2, 2));
	if (r.n == 0 || (r.n == 1 && !is_in_bounds(r.values[0],
				FLOAT_MARGIN, ARBITARY_LIMIT)) || (r.n == 2 && !is_in_bounds(
				r.values[0], FLOAT_MARGIN, ARBITARY_LIMIT)
			&& !is_in_bounds(r.values[1], FLOAT_MARGIN, ARBITARY_LIMIT)))
		return (-1.0f);
	if (r.n == 1)
		return (r.values[0]);
	if (r.values[0] > r.values[1] && is_in_bounds(r.values[1],
			FLOAT_MARGIN, ARBITARY_LIMIT))
		return (r.values[1]);
	return (r.values[0]);
}

t_inter	closer_sphere_inter(t_line *line, t_sphere *sphere)
{
	t_inter	inter;
	float	line_len;

	inter.object = NULL;
	line_len = sphere_inter_line_len(line, sphere);
	if (line_len < 0.f)
		return (inter);
	inter.object_type = sp;
	inter.object = sphere;
	inter.point = translate_point(line->origin,
			scalar_vec(line_len, line->direction));
	return (inter);
}
