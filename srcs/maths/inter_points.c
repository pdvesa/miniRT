//
// Created by Jules Cayot on 5/20/24.
//

#include <ft_maths.h>

t_coordinates	sphere_inter(t_line line, t_sphere sphere)
{
	t_coordinates	inter;
	float			line_len;
	t_vector		cam_to_center;

	cam_to_center = vector_from_points(line.origin, sphere.center);
	line_len = poly_root(dot_product(line.direction, line.direction),
						 dot_product(scalar_vector(2.0f, line.direction), cam_to_center),
						 (dot_product(cam_to_center, cam_to_center) -
						  powf(sphere.diameter, 2)));
	inter = translate_point(line.origin, scalar_vector(line_len, line.direction));
	return (inter);
}
