/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane_inter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcayot <jcayot.student@hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 20:38:24 by jcayot            #+#    #+#             */
/*   Updated: 2024/07/18 20:38:25 by jcayot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT_render.h>

t_inter	plane_inter(t_line *line, t_plane *plan)
{
	t_inter	inter;
	float	line_len;
	float	dot;

	inter.object = NULL;
	dot = dot_product(plan->vector, line->direction);
	if (dot == 0)
		return (inter);
	line_len = dot_product(plan->vector, vector_from_points(line->origin,
				plan->coordinates)) / dot;
	if (line_len < FLOAT_MARGIN)
		return (inter);
	inter.object_type = pl;
	inter.object = plan;
	inter.point = translate_point(line->origin,
			scalar_vec(line_len, line->direction));
	return (inter);
}

int	plane_self_hide(t_ray *ray, t_light *light)
{
	t_inter	inter;
	t_line	cam_to_light;

	cam_to_light.origin = ray->line.origin;
	cam_to_light.direction = vector_from_points(ray->line.origin,
			light->center);
	inter = plane_inter(&cam_to_light, (t_plane *) ray->inter.object);
	if (!inter.object)
		return (0);
	return (point_distance(ray->line.origin, light->center)
		> point_distance(ray->line.origin, inter.point));
}
