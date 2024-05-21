//
// Created by Jules Cayot on 5/21/24.
//

#include <ft_maths.h>

t_coordinates	translate_point(t_coordinates origin, t_vector vector)
{
	t_coordinates	result;

	result.x = origin.x + vector.x;
	result.y = origin.y + vector.y;
	result.z = origin.z + vector.z;
	return (result);
}
