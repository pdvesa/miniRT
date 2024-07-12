//
// Created by Jules Cayot on 5/20/24.
//

#include <ft_maths.h>

t_vector	vector_from_points(t_coordinates origin, t_coordinates destination)
{
	t_vector	result;

	result.x = destination.x - origin.x;
	result.y = destination.y - origin.y;
	result.z = destination.z - origin.z;
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

t_vector	add_vector(t_vector v1, t_vector v2)
{
	t_vector	result;

	result.x = v1.x + v2.x;
	result.y = v1.y + v2.y;
	result.z = v1.z + v2.z;
	return (result);
}

t_vector	normalize_vector(t_vector v)
{
	t_vector	result;
	float		norm;

	norm = sqrtf(powf(v.x, 2.0f) + powf(v.y, 2.0f) + powf(v.z, 2.0f));
	if (norm == 0)
		return (v);
	result.x = v.x / norm;
	result.y = v.y / norm;
	result.z = v.z / norm;
	return (result);
}

float	dot_product(t_vector v1, t_vector v2)
{
	return ((v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z));
}

t_vector	cross_product(t_vector v1, t_vector v2)
{
	t_vector	result;

	result.x = (v1.y * v2.z) - (v1.z * v2.y);
	result.y = (v1.z * v2.x) - (v1.x * v2.z);
	result.z = (v1.x * v2.y) - (v1.y * v2.x);
	return (result);
}
