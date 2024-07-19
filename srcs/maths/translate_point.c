/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   translate_point.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcayot <jcayot.student@hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 20:08:32 by jcayot            #+#    #+#             */
/*   Updated: 2024/07/18 20:08:33 by jcayot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_maths.h>

/**
 * @brief Translates a point by a given vector.
 *
 * This function takes a point in three-dimensional space (origin) and
 * translates it by another vector. The result is a new point after
 * translation.
 *
 * @param origin The original point to be translated.
 * @param vector The vector by which the point should be translated.
 *
 * @return The translated point.
 */

t_coordinates	translate_point(t_coordinates origin, t_vector vector)
{
	t_coordinates	result;

	result.x = origin.x + vector.x;
	result.y = origin.y + vector.y;
	result.z = origin.z + vector.z;
	return (result);
}
