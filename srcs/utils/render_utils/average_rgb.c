/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   average_rgb.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcayot <jcayot.student@hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 14:55:39 by jcayot            #+#    #+#             */
/*   Updated: 2024/08/13 14:55:45 by jcayot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT_render.h>

t_rgb	average_rgb(t_rgb *rgb, u_int n)
{
	t_rgb	average;
	u_int	r;
	u_int	g;
	u_int	b;
	u_int	i;

	i = 0;
	r = 0;
	g = 0;
	b = 0;
	while (i < n)
	{
		r += rgb[i].r;
		g += rgb[i].g;
		b += rgb[i].b;
		i++;
	}
	average.r = r / n;
	average.g = g / n;
	average.b = b / n;
	return (average);
}
