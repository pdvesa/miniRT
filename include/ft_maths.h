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

t_polyroot		poly_root(float a, float b, float c);
float			inter_root_linelen(t_polyroot roots);

t_vector		vector_from_points(t_coordinates origin,
					t_coordinates destination);
t_vector		coordinates_to_vector(t_coordinates coordinates);
t_vector		normalize_vector(t_vector v);

t_vector		scalar_vector(float scalar, t_vector v);
t_vector		add_vector(t_vector v1, t_vector v2);
float			dot_product(t_vector v1, t_vector v2);
t_vector		cross_product(t_vector v1, t_vector v2);

t_coordinates	translate_point(t_coordinates origin, t_vector vector);

#endif //FT_MATHS_H
