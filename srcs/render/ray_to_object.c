//
// Created by jules on 11/06/2024.
//

#include <miniRT_render.h>

t_vector	ray_direction(t_camera *cam, t_image_size s, t_pixel_cdts p)
{
	t_vector		ray_vector;
	t_coordinates	projection_point;
	float			focal_len;
	t_vector		v_up;
	t_vector		v_right;

	focal_len = s.W/(2 * tanf(cam->fov / 2));
	projection_point.x = (((2.0f * p.x) / s.W) - 1) * (s.W / 2.0f * focal_len);
	projection_point.y = (1 - ((2.0f * p.y) / s.H)) * (s.H / 2.0f * focal_len);
	projection_point.z = focal_len * -1.0f;
	v_up = orthogonal_vector(cam->vector, 1, 1);
	v_right = cross_product(cam -> vector, v_up);
	ray_vector = add_vector(scalar_vector(projection_point.x, v_right),
							scalar_vector(projection_point.y, v_up));
	ray_vector = add_vector(ray_vector, scalar_vector(focal_len, cam -> vector));
	return (ray_vector);
}

void	closer_obj(t_line *line, void **obj, t_inter_point (*f) (t_line*, void*), t_inter_point	*closer)
{
	t_inter_point	competidor;
	int 			i;

	i = 0;
	while (obj[i])
	{
		competidor = f(line, obj[i]);
		if (point_distance(line->origin, competidor.coordinates) < point_distance(line->origin, closer->coordinates))
			*closer = competidor;
		i++;
	}
}

t_inter_point	get_closer_inter(t_line *line, t_scene *scene)
{
	t_inter_point	closer;

	closer.coordinates = new_far_point();
	closer_obj(line, scene->sphere, (t_inter_point (*)(t_line*, void*)) &sphere_inter, &closer);
	closer_obj(line, scene->plane, (t_inter_point (*)(t_line*, void*)) &plane_inter, &closer);
	closer_obj(line, scene->cylinder, (t_inter_point (*)(t_line*, void*)) &cylinder_inter, &closer);
	return (closer);
}


t_ray	ray_to_object(t_scene *scene, int cam_i, t_image_size s, t_pixel_cdts p)
{
	t_ray	ray;

	ray.line.origin = scene->camera[cam_i]->center;
	ray.line.direction = ray_direction(scene->camera[cam_i], s, p);
	ray.inter_point = get_closer_inter(&ray.line, scene);
	return (ray);
}
