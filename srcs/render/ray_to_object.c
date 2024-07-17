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
	ray_vector = add_vector(scalar_vec(scalar_right, vp->v_right),
		scalar_vec(scalar_up, vp->v_up));
	ray_vector = add_vector(ray_vector,
		scalar_vec(vp->cam_scalar, vp->cam->vector));
	return (normalize_vector(ray_vector));
}

void	closer_obj(t_line *line, t_objs_inter objs_inter,
							t_inter *closer)
{
	t_inter	competidor;
	float	competidor_distance;
	int		i;

	i = 0;
	while (objs_inter.objects[i])
	{
		competidor = objs_inter.f(line, objs_inter.objects[i]);
		if (competidor.object)
		{
			competidor_distance = point_distance(line->origin, competidor.point);
			if (competidor_distance > FLOAT_MARGIN && (!closer->object ||
			competidor_distance < point_distance(line->origin, closer->point)))
				*closer = competidor;
		}
		i++;
	}
}

t_inter	get_closer_inter(t_line *line, t_scene *scene)
{
	t_inter	closer;

	closer.object = NULL;
	closer_obj(line, (t_objs_inter) {(void **) scene->sphere,
		(t_inter (*)(t_line*, void*)) &closer_sphere_inter}, &closer);
	closer_obj(line, (t_objs_inter) {(void **) scene->plane,
		(t_inter (*)(t_line*, void*)) &plane_inter}, &closer);
	closer_obj(line, (t_objs_inter) {(void **) scene->cylinder,
	 (t_inter (*)(t_line*, void*)) &closer_cylinder_inter}, &closer);

	return (closer);
}

t_ray	ray_to_object(t_scene *scene, t_viewport *viewport, t_pixel_cdts *p)
{
	t_ray	ray;

	ray.line.origin = scene->camera->center;
	ray.line.direction = ray_direction(viewport, p);
	ray.inter = get_closer_inter(&ray.line, scene);
	return (ray);
}
