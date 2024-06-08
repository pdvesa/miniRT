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

t_vector	add_vector(t_vector v1, t_vector v2)
{
	t_vector	result;

	result.x = v1.x + v2.x;
	result.y = v1.y + v2.y;
	result.z = v1.z + v2.z;
	return (result);
}

t_vector	substract_vector(t_vector v1, t_vector v2)
{
	t_vector	result;

	result.x = v1.x - v2.x;
	result.y = v1.y - v2.y;
	result.z = v1.z - v2.z;
	return (result);
}

t_vector	orthogonal_vector(t_vector v)
{
	t_vector	orthogonal;

	if (v.x != 0 || v.y != 0)
	{
		orthogonal.x = 0;
		orthogonal.y = v.z;
		orthogonal.z = -1.0f * v.y;
	}
	else if (v.z != 0)
	{
		orthogonal.x = -1.0f * v.z;
		orthogonal.y = 0;
		orthogonal.z = v.x;
	}
	else
	{
		orthogonal.x = 1;
		orthogonal.y = 0;
		orthogonal.z = 0;
	}
	return (orthogonal);
}

t_vector	normalize_vector(t_vector v)
{
	t_vector	result;
	float		norm;

	norm = sqrtf(powf(v.x, 2.0f) + powf(v.y, 2.0f) + powf(v.z, 2.0f));
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
