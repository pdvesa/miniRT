//
// Created by Jules Cayot on 5/21/24.
//

#include <ft_maths.h>

t_coordinates new_far_point()
{
	t_coordinates	far_point;

	far_point.x = MAXFLOAT;
	far_point.y = MAXFLOAT;
	far_point.z = MAXFLOAT;
	return (far_point);
}
