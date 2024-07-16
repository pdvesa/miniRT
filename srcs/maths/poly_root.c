//
// Created by Jules Cayot on 21/05/2024.
//

#include <ft_maths.h>

t_polyroot	poly_root(float a, float b, float c)
{
	t_polyroot roots;
	float discriminant;

	roots.values[0] = 0;
	roots.values[1] = 0;
	discriminant = b * b - (4.0f * a * c);
	if (discriminant < 0.0f)
		roots.n = 0;
	else if (discriminant == 0.0f)
	{
		roots.n = 1;
		roots.values[0] = -b / (2.0f * a);
	} else
	{
		roots.n = 2;
		roots.values[0] = (-b + sqrtf(discriminant)) / (2.0f * a);
		roots.values[1] = (-b - sqrtf(discriminant)) / (2.0f * a);
	}
	return roots;
}

float	inter_root_linelen(t_polyroot roots)
{
	if (roots.n == 0 || (roots.n == 1 && roots.values[0] < FLOAT_MARGIN)
		|| (roots.n == 2 && roots.values[0] < FLOAT_MARGIN && roots.values[1] < FLOAT_MARGIN))
		return (-1.0f);
	if (roots.n == 1)
		return (roots.values[0]);
	else
	{
		if (roots.values[0] > roots.values[1] && roots.values[1] > FLOAT_MARGIN)
			return (roots.values[1]);
		else
			return (roots.values[0]);
	}
}
