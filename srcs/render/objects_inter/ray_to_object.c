/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_to_object.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcayot <jcayot.student@hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 20:29:11 by jcayot            #+#    #+#             */
/*   Updated: 2024/07/18 20:29:12 by jcayot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniRT_render.h"

t_vector	ray_direction(t_vp *vp, t_pxl_cdts *p)
{
	t_vector		ray_vector;
	float			scalar_right;
	float			scalar_up;

	scalar_right = ((float) vp->scene->cam->fov / 180.f)
		* (((float) p->x - ((float) vp->w / 2.0f)) / ((float) vp->w / 2.0f));
	scalar_up = (((float) vp->h / (float) vp->w) * (float) vp->scene->cam->fov / 180.f)
		* (((float) p->y - ((float) vp->h / 2.0f)) / ((float) vp->h / 2.0f));
	ray_vector = add_vector(scalar_vec(scalar_right, vp->v_right),
			scalar_vec(scalar_up, vp->v_up));
	ray_vector = add_vector(ray_vector,
			scalar_vec(vp->cam_scalar, vp->scene->cam->vect));
	return (normalize_vector(ray_vector));
}

void	closer_obj(t_line *line, void **objects, t_inter (*f) (t_line*, void*),
			t_inter *closer)
{
	t_inter	compet;
	float	compet_dist;
	int		i;

	i = 0;
	while (objects[i])
	{
		compet = f(line, objects[i]);
		if (compet.object)
		{
			compet_dist = point_distance(line->origin, compet.point);
			if (is_in_bounds(compet_dist, FLOAT_MARGIN, ARBITARY_LIMIT)
				&& (!closer->object || compet_dist
					< point_distance(line->origin, closer->point)))
				*closer = compet;
		}
		i++;
	}
}

t_inter	get_closer_inter(t_line *line, t_scene *scene)
{
	t_inter	closer;

	closer.object = NULL;
	closer_obj(line, (void **) scene->sphere,
		(t_inter (*)(t_line *, void *)) &closer_sphere_inter, &closer);
	closer_obj(line, (void **) scene->plane,
		(t_inter (*)(t_line *, void *)) &plane_inter, &closer);
	closer_obj(line, (void **) scene->cylinder,
		(t_inter (*)(t_line *, void *)) &closer_cylinder_inter, &closer);
	return (closer);
}

t_ray ray_to_object(t_vp* vp, t_pxl_cdts* p)
{
	t_ray	ray;

	ray.line.origin = vp->scene->cam->center;
	ray.line.direction = ray_direction(vp, p);
	ray.inter = get_closer_inter(&ray.line, vp->scene);
	return (ray);
}
