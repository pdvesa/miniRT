//
// Created by jules on 11/06/2024.
//

#include <miniRT_render.h>

t_vector	ray_direction(t_viewport *vp, t_pixel_cdts *p)
{
	t_vector		ray_vector;
	float			scalar_right;
	float			scalar_up;

	scalar_right = ((float) vp->cam->fov / 180.f)
				   * (((float) p->x - ((float) vp->w / 2.0f)) / ((float) vp->w / 2.0f));
	scalar_up = (((float) vp->h / (float) vp->w) * (float) vp->cam->fov / 180.f)
				* (((float) p->y - ((float) vp->h / 2.0f)) / ((float) vp->h / 2.0f));
	ray_vector = add_vector(scalar_vector(scalar_right, vp->v_right),
							scalar_vector(scalar_up, vp->v_up));
	ray_vector = add_vector(ray_vector, vp->cam->vector);
	return (normalize_vector(ray_vector));
}

void	closer_obj(t_line *line, t_objs_inter objs_inter,
							t_inter_point *closer, void *self)
{
	t_inter_point	competidor;
	int 			i;

	i = 0;
	while (objs_inter.objects[i])
	{
		if (objs_inter.objects[i] != self)
		{
			competidor = objs_inter.f(line, objs_inter.objects[i]);
			if (competidor.object && (!closer->object ||
					point_distance(line->origin, competidor.coordinates)
					< point_distance(line->origin, closer->coordinates)))
				*closer = competidor;
		}
		i++;
	}
}

t_inter_point	get_closer_inter(t_line *line, t_scene *scene, void *self)
{
	t_inter_point	closer;

	closer.object = NULL;
	closer_obj(line, (t_objs_inter) {(void **) scene->sphere,
		(t_inter_point (*)(t_line*, void*)) &closer_sphere_inter}, &closer, self);
	closer_obj(line, (t_objs_inter) {(void **) scene->plane,
		(t_inter_point (*)(t_line*, void*)) &plane_inter}, &closer, self);
	closer_obj(line, (t_objs_inter) {(void **) scene->cylinder,
	 (t_inter_point (*)(t_line*, void*)) &cylinder_inter}, &closer, self);

	return (closer);
}

t_ray	ray_to_object(t_scene *scene, t_viewport *viewport, t_pixel_cdts *p)
{
	t_ray	ray;

	ray.line.origin = scene->camera->center;
	ray.line.direction = ray_direction(viewport, p);
	ray.inter_point = get_closer_inter(&ray.line, scene, NULL);
	return (ray);
}
