//
// Created by Jules Cayot on 13/05/2024.
//

#ifndef FT_MATHS_H
# define FT_MATHS_H

# include <math.h>

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
	float	values[2];
}	t_polyroot;

float		point_distance(t_coordinates p1, t_coordinates p2);

t_polyroot	poly_root(float a, float b, float c);

t_vector	vector_from_points(t_coordinates c1, t_coordinates c2);
t_vector	scalar_vector(float scalar, t_vector v);
t_vector	add_vector(t_vector v1, t_vector v2);
t_vector	substract_vector(t_vector v1, t_vector v2);
t_vector orthogonal_vector(t_vector v, float n1, float n2);
t_vector	normalize_vector(t_vector v);
float		dot_product(t_vector v1, t_vector v2);
t_vector	cross_product(t_vector v1, t_vector v2);

t_coordinates	translate_point(t_coordinates origin, t_vector vector);

t_coordinates new_far_point();

#endif //FT_MATHS_H
