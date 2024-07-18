/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point_distance.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcayot <jcayot.student@hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 20:06:05 by jcayot            #+#    #+#             */
/*   Updated: 2024/07/18 20:06:07 by jcayot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_maths.h>

float	point_distance(t_coordinates p1, t_coordinates p2)
{
	return (sqrtf(powf(p2.x - p1.x, 2)
			+ powf(p2.y - p1.y, 2) + powf(p2.z - p1.z, 2)));
}
