/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_rgb.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcayot <jcayot.student@hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 21:02:31 by jcayot            #+#    #+#             */
/*   Updated: 2024/07/18 21:02:33 by jcayot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT_render.h>

t_rgb	add_rgb(t_rgb rgb1, t_rgb rgb2)
{
	t_rgb	result;

	result.r = rgb1.r + rgb2.r;
	if (result.r > 255)
		result.r = 255;
	result.g = rgb1.g + rgb2.g;
	if (result.g > 255)
		result.g = 255;
	result.b = rgb1.b + rgb2.b;
	if (result.b > 255)
		result.b = 255;
	return (result);
}
