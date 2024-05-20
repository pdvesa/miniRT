//
// Created by Jules Cayot on 5/20/24.
//

#include <ft_maths.h>

float	point_distance(t_coordinates p1, t_coordinates p2)
{
	return (sqrt(pow(p2.x - p1.x, 2) + pow(p2.y - p1.y, 2) + pow(p2.z - p1.z, 2)));
}
