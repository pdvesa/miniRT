//
// Created by jules on 10/06/2024.
//

#include <ft_maths.h>

t_vector	all_non_null(t_vector v, float a, float b)
{
	t_vector	orthogonal;

	orthogonal.x = a;
	orthogonal.y = b;
	orthogonal.z = -1.0f * (((v.x * a) + v.y * b) / v.z);
	return (orthogonal);
}

t_vector	x_null(t_vector v, float b)
{
	t_vector	orthogonal;

	orthogonal.x = 0;
	orthogonal.y = b;
	orthogonal.z = -1.0f * ((v.y * b) / v.z);
	return (orthogonal);
}

t_vector	y_null(t_vector v, float a)
{
	t_vector	orthogonal;

	orthogonal.x = a;
	orthogonal.y = 0;
	orthogonal.z = -1.0f * ((v.x * a) / v.z);
	return (orthogonal);
}

t_vector	z_null(t_vector v, float a)
{
	t_vector	orthogonal;

	orthogonal.x = a;
	orthogonal.y = -1.0f * ((v.x * a) / v.y);
	orthogonal.z = 0;
	return (orthogonal);
}

t_vector	x_non_null(float b, float c)
{
	t_vector	orthogonal;

	orthogonal.x = 0;
	orthogonal.y = b;
	orthogonal.z = c;
	return (orthogonal);
}

t_vector	y_non_null(float a, float c)
{
	t_vector	orthogonal;

	orthogonal.x = a;
	orthogonal.y = 0;
	orthogonal.z = c;
	return (orthogonal);
}

t_vector	z_non_null(float a, float b)
{
	t_vector	orthogonal;

	orthogonal.x = a;
	orthogonal.y = b;
	orthogonal.z = 0;
	return (orthogonal);
}

t_vector	all_null()
{
	t_vector	orthogonal;

	orthogonal.x = 0;
	orthogonal.y = 0;
	orthogonal.z = 0;
	return (orthogonal);
}

t_vector orthogonal_vector(t_vector v, float n1, float n2)
{
	if (v.x != 0 && v.y != 0 && v.z != 0)
		return (all_non_null(v, n1, n2));
	if (v.y != 0 && v.z != 0)
		return (x_null(v, n2));
	if (v.x != 0 && v.z != 0)
		return (y_null(v, n1));
	if (v.x != 0 && v.y != 0)
		return (z_null(v, n1));
	if (v.x != 0)
		return (x_non_null(n2, n1));
	if (v.y != 0)
		return (y_non_null(n1, n2));
	if (v.z != 0)
		return (z_non_null(n1, n2));
	return (all_null());
}
