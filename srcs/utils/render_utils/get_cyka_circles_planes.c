//
// Created by jules on 11/06/2024.
//

#include <render_utils.h>

void	get_cyka_circles_planes(t_cylinder *cylinder, t_plane *result)
{
	int	i;

	i = 0;
	while (i < 2)
	{
		result[i].vector = cylinder->vector;
		i++;
	}
	result[0].coordinates = translate_point(cylinder->center,
		scalar_vec(cylinder->height / 2.0f, cylinder->vector));
	result[1].coordinates = translate_point(cylinder->center,
		scalar_vec(-1.0f * (cylinder->height / 2.0f), cylinder->vector));
}
