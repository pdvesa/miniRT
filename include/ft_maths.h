/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_maths.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcayot <jcayot.student@hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 18:18:28 by jcayot            #+#    #+#             */
/*   Updated: 2024/07/11 18:18:29 by jcayot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MATHS_H
# define FT_MATHS_H

# include <math.h>

# ifndef FLOAT_MARGIN
#  define FLOAT_MARGIN 0.005f
# endif //FLOAT_MARGIN

typedef struct s_vector
{
	float	x;
	float	y;
	float	z;
}	t_vector;

typedef struct s_coordinates
{
	float	x;
	float	y;
	float	z;
}	t_coordinates;

typedef struct s_polyroot
{
	int		n;
	float	values[2];
}	t_polyroot;

float			point_distance(t_coordinates p1, t_coordinates p2);
int				is_in_bounds(float value, float min, float max);

t_polyroot		poly_root(float a, float b, float c);

t_vector		vect_from_points(t_coordinates origin,
					t_coordinates destination);
t_vector		normalize_vector(t_vector v);

t_vector		scalar_vec(float scalar, t_vector v);
t_vector		add_vector(t_vector v1, t_vector v2);
float			dot_product(t_vector v1, t_vector v2);
t_vector		cross_product(t_vector v1, t_vector v2);

t_coordinates	translate_point(t_coordinates origin, t_vector vector);

#endif //FT_MATHS_H
