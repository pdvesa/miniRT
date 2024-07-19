/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_in_bounds.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcayot <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 16:30:35 by jcayot            #+#    #+#             */
/*   Updated: 2024/07/19 16:33:02 by jcayot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_maths.h>

/**
 * @brief Check if a value is within the specified range.
 *
 * This function takes a value and two boundaries,
 * and checks if the value is within the range defined by the boundaries.
 *
 * @param value The value to check.
 * @param min The minimum boundary of the range.
 * @param max The maximum boundary of the range.
 *
 * @return True if the value is within the range, false otherwise.
 */

int	is_in_bounds(float value, float min, float max)
{
	return (!isnanf(value) && value > min && value < max);
}
