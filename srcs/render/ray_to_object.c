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

t_ray	ray_to_object(t_scene *scene, t_viewport *viewport, t_pixel_cdts *p)
{
	t_ray	ray;

	ray.line.origin = scene->camera->center;
	ray.line.direction = ray_direction(viewport, p);
	ray.inter_point = get_closer_inter(&ray.line, scene, NULL);
	return (ray);
}
