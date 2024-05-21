//
// Created by Jules Cayot on 5/20/24.
//

#include <ft_maths.h>

t_vector	vector_from_points(t_coordinates c1, t_coordinates c2)
{
	t_vector	result;

	result.x = c1.x - c2.x;
	result.y = c1.y - c2.y;
	result.z = c1.z - c2.z;
	return (result);
}

t_vector	scalar_vector(float scalar, t_vector v)
{
	t_vector	result;

	result.x = v.x * scalar;
	result.y = v.y * scalar;
	result.z = v.z * scalar;
	return (result);
}

float	dot_product(t_vector v1, t_vector v2)
{
	return ((v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z));
}
