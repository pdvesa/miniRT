//
// Created by jules on 11/06/2024.
//

#include <miniRT_render.h>

t_vector	ray_direction(t_camera *cam, t_image_size *s, t_pixel_cdts *p)
{
	t_vector		direction;
	t_coordinates	projection_point;
	float			focal_len;

	focal_len = cosf(((float) cam->fov * ((float) M_PI / 180.0f)) / 2.0f);
	projection_point = translate_point(cam->center, scalar_vector(focal_len, cam->vector));
	projection_point.x += (sinf((((float) cam->fov) * ((float) M_PI / 180.f)) / 2.0f)) * ((2.0f * ((float) p->x + 0.5f) / (float) s->W) - 1.0f);
	projection_point.y += (sinf(((((float) cam->fov) * (9.0f/16.0f)) * ((float) M_PI / 180.f)) / 2.0f));
	direction = vector_from_points(cam->center, projection_point);
	direction = normalize_vector(direction);
	return (direction);
}

t_ray	ray_to_object(t_scene *scene, t_image_size *s, t_pixel_cdts *p)
{
	t_ray	ray;

	ray.line.origin = scene->camera->center;
	ray.line.direction = ray_direction(scene->camera, s, p);
	ray.inter_point = get_closer_inter(&ray.line, scene, NULL);
	return (ray);
}
