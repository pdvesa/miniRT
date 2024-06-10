//
// Created by Jules Cayot on 5/20/24.
//

#include <miniRT_render.h>

t_inter_point	sphere_inter(t_line *line, t_sphere *sphere)
{
	t_inter_point	inter;
	t_polyroot		roots;
	float			line_len;
	t_vector		cam_to_center;

	inter.coordinates = new_far_point();
	inter.object_type = sp;
	inter.object = sphere;
	cam_to_center = vector_from_points(line->origin, sphere->center);
	roots = poly_root(dot_product(line->direction, line->direction),
						 dot_product(scalar_vector(2.0f, line->direction), cam_to_center),
						 (dot_product(cam_to_center, cam_to_center) -
						  powf(sphere->diameter, 2)));
	if (roots.n == 0)
		return (inter);
	else if (roots.n == 1)
		line_len = roots.values[0];
	else
	{
		if (roots.values[0] > roots.values[1])
			line_len = roots.values[1];
		else
			line_len = roots.values[0];
	}
	inter.coordinates = translate_point(line->origin, scalar_vector(line_len, line->direction));
	return (inter);
}

t_inter_point	plane_inter(t_line *line, t_plane *plan)
{
	t_inter_point	inter;
	float			line_len;
	float			dot;

	inter.coordinates = new_far_point();
	inter.object_type = pl;
	inter.object = plan;
	dot = dot_product(plan->vector, line->direction);
	if (dot < 0)
		return (inter);
	else if (dot == 0)
		return (inter); //TODO UNCORRECT !!!!
	line_len = dot_product(plan->vector, vector_from_points(plan->coordinates, line->origin)) / dot;
	inter.coordinates = translate_point(line->origin, scalar_vector(line_len, line->direction));
	return (inter);
}

t_inter_point	cylinder_inter(t_line *line, t_cylinder *cylinder)
{

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
