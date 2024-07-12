//
// Created by jules on 11/07/2024.
//

# include <ft_maths.h>

t_vector	coordinates_to_vector(t_coordinates coordinates)
{
	t_vector	vector;

	vector.x = coordinates.x;
	vector.y = coordinates.y;
	vector.z = coordinates.z;
	return (vector);
}
