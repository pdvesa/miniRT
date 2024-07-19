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

t_coordinates	translate_point(t_coordinates origin, t_vector vector)
{
	t_coordinates	result;

	result.x = origin.x + vector.x;
	result.y = origin.y + vector.y;
	result.z = origin.z + vector.z;
	return (result);
}
