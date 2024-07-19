/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal_to_inter.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcayot <jcayot.student@hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 20:42:05 by jcayot            #+#    #+#             */
/*   Updated: 2024/07/18 20:42:07 by jcayot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//
// Created by jules on 08/06/2024.
//

#include <miniRT_render.h>

t_vector	normal_inter_sphere(t_ray *ray)
{
	t_vector	result;

	result = vector_from_points(((t_sphere *) ray->inter.object)->center,
			ray->inter.point);
	result = normalize_vector(result);
	return (result);
}

t_vector	normal_inter_cyka(t_ray *ray)
{
	t_vector	result;
	float		v_dist;
	t_cylinder	*cyl;

	cyl = (t_cylinder *) ray->inter.object;
	v_dist = sqrtf(powf(point_distance(ray->inter.point, cyl->center), 2.f)
			- powf(cyl->diameter / 2.f, 2.f));
	if (dot_product(cyl->vector,
			vector_from_points(cyl->center, ray->inter.point)) < 0.f)
		v_dist *= -1.f;
	result = vector_from_points(translate_point(cyl->center,
				scalar_vec(v_dist, cyl->vector)), ray->inter.point);
	result = normalize_vector(result);
	return (result);
}

t_vector	get_normal_to_inter(t_ray *ray)
{
	t_vector	normal;

	if (ray->inter.object_type == sp)
		return (normal_inter_sphere(ray));
	if (ray->inter.object_type == cyka)
		return (normal_inter_cyka(ray));
	if (ray->inter.object_type == pl)
		normal = ((t_plane *) ray->inter.object)->vector;
	else
		normal = ((t_cylinder *) ray->inter.object)->vector;
	return (normal);
}
