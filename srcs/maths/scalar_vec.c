/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scalar_vec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcayot <jcayot.student@hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 20:11:36 by jcayot            #+#    #+#             */
/*   Updated: 2024/07/18 20:11:37 by jcayot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_maths.h>

/**
 * Calculates the scalar multiple of a vector.
 *
 * @param scalar The scalar value to multiply the vector by.
 * @param v The vector to be multiplied.
 * @return The result of multiplying the vector by the scalar.
 */

t_vector	scalar_vec(float scalar, t_vector v)
{
	t_vector	result;

	result.x = v.x * scalar;
	result.y = v.y * scalar;
	result.z = v.z * scalar;
	return (result);
}
