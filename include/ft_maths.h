//
// Created by Jules Cayot on 13/05/2024.
//

#ifndef FT_MATHS_H
# define FT_MATHS_H

# include <math.h>
# include <miniRT.h>

typedef struct	s_vector
{
	float	x;
	float	y;
	float	z;
}	t_vector;

typedef struct	s_coordinates
{
	float	x;
	float	y;
	float	z;
}	t_coordinates;

float	point_distance(t_coordinates p1, t_coordinates p2);

#endif //FT_MATHS_H
