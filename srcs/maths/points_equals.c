//
// Created by jules on 18/06/2024.
//

#include <ft_maths.h>

int point_equals(t_coordinates p1, t_coordinates p2)
{
	const float tolerance = 0.001f;

	return ((fabs(p1.x - p2.x) < tolerance) &&
			(fabs(p1.y - p2.y) < tolerance) &&
			(fabs(p1.z - p2.z) < tolerance));
}
