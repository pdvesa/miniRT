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

typedef struct	s_polyroot
{
	int		n;
	float	roots[2];
}	t_polyroot;

float		point_distance(t_coordinates p1, t_coordinates p2);

t_polyroot	poly_root(float a, float b, float c);

t_vector	vector_from_points(t_coordinates c1, t_coordinates c2);
t_vector	scalar_vector(float scalar, t_vector v);
float		dot_product(t_vector v1, t_vector v2);

t_coordinates	translate_point(t_coordinates origin, t_vector vector);

#endif //FT_MATHS_H
