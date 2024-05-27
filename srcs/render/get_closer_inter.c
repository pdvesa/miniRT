//
// Created by Jules Cayot on 5/20/24.
//

#include <miniRT_render.h>

t_coordinates	sphere_inter(t_line *line, t_sphere *sphere)
{
	t_coordinates	inter;
	t_polyroot		roots;
	float			line_len;
	t_vector		cam_to_center;

	cam_to_center = vector_from_points(line->origin, sphere->center);
	roots = poly_root(dot_product(line->direction, line->direction),
						 dot_product(scalar_vector(2.0f, line->direction), cam_to_center),
						 (dot_product(cam_to_center, cam_to_center) -
						  powf(sphere->diameter, 2)));
	if (roots.n == 0)
		return (new_far_point());
	else if (roots.n == 1)
		line_len = roots.values[0];
	else
	{
		if (roots.values[0] > roots.values[1])
			line_len = roots.values[1];
		else
			line_len = roots.values[0];
	}
	inter = translate_point(line->origin, scalar_vector(line_len, line->direction));
	return (inter);
}

t_coordinates	plane_inter(t_line *line, t_plane *plan)
{
	t_coordinates	inter;
	float			line_len;
	float			dot;

	dot = dot_product(plan->vector, line->direction);
	if (dot < 0)
		return (new_far_point());
	else if (dot == 0)
		return (new_far_point()); //TODO UNCORRECT !!!!
	line_len = dot_product(plan->vector, vector_from_points(plan->coordinates, line->origin)) / dot;
	inter = translate_point(line->origin, scalar_vector(line_len, line->direction));
	return (inter);
}

t_coordinates	cylinder_inter(t_line *line, t_cylinder *cylinder)
{
	t_coordinates	inter;
	t_polyroot		roots;
	float			line_len;
	t_vector		A;
	t_vector		B;

	A = substract_vector(line->direction,scalar_vector(
			dot_product(line->direction, cylinder->vector), cylinder->vector));
	B = substract_vector(vector_from_points(line->origin, cylinder->center),
						 scalar_vector(dot_product(
								 vector_from_points(line->origin, cylinder->center),
								 cylinder->vector), cylinder->vector));
	roots = poly_root(dot_product(A, A), 2.0f * dot_product(A, B), dot_product(B, B) - powf(cylinder->diameter, 2.0f));
	if (roots.n == 0)
		return (new_far_point());
	else if (roots.n == 1)
		line_len = roots.values[0];
	else
	{
		if (roots.values[0] > roots.values[1])
			line_len = roots.values[1];
		else
			line_len = roots.values[0];
	}
	inter = translate_point(line->origin, scalar_vector(line_len, line->direction));
	return (inter);
}

void	closer_obj(t_line *line, void **obj, t_coordinates (*f) (t_line*, void*), t_coordinates *closer)
{
	t_coordinates	competidor;
	int 			i;

	i = 0;
	while (obj[i])
	{
		competidor = f(line, obj[i]);
		if (point_distance(line->origin, competidor) < point_distance(line->origin, *closer))
			*closer = competidor;
		i++;
	}
}

t_coordinates	get_closer_inter(t_line *line, t_scene *scene)
{
	t_coordinates	closer;

	closer = new_far_point();
	closer_obj(line, scene->sphere, (t_coordinates (*)(t_line*, void*)) &sphere_inter, &closer);
	closer_obj(line, scene->plane, (t_coordinates (*)(t_line*, void*)) &plane_inter, &closer);
	closer_obj(line, scene->cylinder, (t_coordinates (*)(t_line*, void*)) &cylinder_inter, &closer);
	return (closer);
}
