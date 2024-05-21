//
// Created by Jules Cayot on 21/05/2024.
//

#include <ft_maths.h>

t_polyroot	poly_root(float a, float b, float c)
{
	t_polyroot	roots;
	float		discriminant;

	roots.n = 0;
	roots.roots[0] = 0;
	roots.roots[0] = 1;
	discriminant = powf(b, 2) - (4.0f * a * c);
	if (discriminant < 0.f)
		roots.n = 0;
	else if (discriminant == 0.f)
	{
		roots.n = 1;
		roots.roots[0] = (-b/(2 * a));
	}
	else
	{
		roots.n = 2;
		roots.roots[0] = (-b + sqrtf(discriminant))/(2 * a);
		roots.roots[1] = (-b - sqrtf(discriminant))/(2 * a);
	}
	return (roots);
}
