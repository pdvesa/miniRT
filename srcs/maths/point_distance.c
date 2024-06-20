//
// Created by jules on 20/06/2024.
//

#include <ft_maths.h>

float	point_distance(t_coordinates p1, t_coordinates p2)
{
	return sqrtf(powf(p2.x - p1.x, 2) + powf(p2.y - p1.y, 2));
}
