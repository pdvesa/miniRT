/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normalize_vector.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcayot <jcayot.student@hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 20:13:36 by jcayot            #+#    #+#             */
/*   Updated: 2024/07/18 20:13:40 by jcayot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_maths.h>

/**
 * @brief Normalize a given vector.
 *
 * @param v The vector to be normalized.
 * @return The normalized vector.
 */

t_vector	normalize_vector(t_vector v)
{
	t_vector	result;
	float		norm;

	norm = sqrtf(powf(v.x, 2.0f) + powf(v.y, 2.0f) + powf(v.z, 2.0f));
	if (norm == 0 || isnanf(norm))
		return (v);
	result.x = v.x / norm;
	result.y = v.y / norm;
	result.z = v.z / norm;
	return (result);
}
