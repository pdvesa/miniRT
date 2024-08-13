/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vect_from_points.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcayot <jcayot.student@hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 20:10:58 by jcayot            #+#    #+#             */
/*   Updated: 2024/07/18 20:10:59 by jcayot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_maths.h>

/**
 * @brief Calculates a vector from two given points.
 *
 * @param origin The origin point.
 * @param destination The destination point.
 *
 * @return The calculated vector.
 */

t_vector	vect_from_points(t_coordinates origin, t_coordinates destination)
{
	t_vector	result;

	result.x = destination.x - origin.x;
	result.y = destination.y - origin.y;
	result.z = destination.z - origin.z;
	return (result);
}
