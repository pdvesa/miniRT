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

	result.r = 255 - sqrt((pow(255 - rgb1.r, 2) + pow(255 - rgb2.r, 2)) / 2);
	result.g = 255 - sqrt((pow(255 - rgb1.g, 2) + pow(255 - rgb2.g, 2)) / 2);
	result.b = 255 - sqrt((pow(255 - rgb1.b, 2) + pow(255 - rgb2.b, 2)) / 2);
	return (result);
}
