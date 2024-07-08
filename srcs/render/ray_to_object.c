//
// Created by jules on 11/06/2024.
//

#include <miniRT_render.h>

t_vector	ray_direction(t_camera *cam, t_image_size *s, t_pixel_cdts *p)
{
	t_vector		ray_vector;
	t_vector		v_up;
	t_vector		v_right;
	float			scalar_right;
	float			scalar_up;

	v_up = orthogonal_vector(cam->vector, .0f, 1.0f);
	v_right = cross_product(cam->vector, v_up);
	scalar_right = ((float) cam->fov / 180.f) * (((float) p->x - ((float) s->W / 2.0f)) / ((float) s->W / 2.0f));
	scalar_up = (((float) s->H / (float) s->W) * (float) cam->fov / 180.f) * (((float) p->y - ((float) s->H / 2.0f)) / ((float) s->H / 2.0f));
	ray_vector = add_vector(scalar_vector(scalar_right, v_right), scalar_vector(scalar_up, v_up));
	ray_vector = add_vector(ray_vector, cam->vector);
//	printf("v_up : %f, %f, %f scalar : %f\n", v_up.x, v_up.y, v_up.z, scalar_up);
//	printf("v_right : %f, %f, %f, scalar : %f\n", v_right.x, v_right.y, v_right.z, scalar_right);
//	printf("cam : %f, %f, %f, scalar : %f\n", cam->vector.x, cam->vector.y, cam->vector.z, 1.0f - (fabsf(scalar_right) + fabsf(scalar_up)));
//	printf("ray vector : %f, %f, %f\n", normalize_vector(ray_vector).x, normalize_vector(ray_vector).y,
//		   normalize_vector(ray_vector).z);
	return (normalize_vector(ray_vector));
}

t_ray	ray_to_object(t_scene *scene, t_image_size *s, t_pixel_cdts *p)
{
	t_ray	ray;

	ray.line.origin = scene->camera->center;
	ray.line.direction = ray_direction(scene->camera, s, p);
	ray.inter_point = get_closer_inter(&ray.line, scene, NULL);
	return (ray);
}
