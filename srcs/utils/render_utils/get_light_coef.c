/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_light_coef.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcayot <jcayot.student@hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 21:05:34 by jcayot            #+#    #+#             */
/*   Updated: 2024/07/18 21:05:35 by jcayot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT_render.h>

float	get_light_coef(t_vector vect_to_light, t_vector normal_inter)
{
	float	light_coef;

	light_coef = dot_product(vect_to_light, normal_inter);
	if (light_coef < 0.0f)
		light_coef *= -1.0f;
	return (light_coef);
}
