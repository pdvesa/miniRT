/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_render_data.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcayot <jcayot.student@hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 14:47:36 by jcayot            #+#    #+#             */
/*   Updated: 2024/08/13 14:47:37 by jcayot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT_render.h>

t_render_data	init_single_data(t_vp *vp, void *render, t_aa_data *aa_data,
					void (*render_f) (t_vp*, t_pxl_cdts*, t_aa_data*, void*))
{
	t_render_data	data;

	data.vp = vp;
	data.aa_data = aa_data;
	data.render = render;
	data.x_min = 0;
	data.x_max = vp->w;
	data.y_min = 0;
	data.y_max = vp->h;
	data.render_f = render_f;
	return (data);
}

void	multi_render_data(t_render_data *data, t_vp *vp, void *render,
			t_aa_data *aa_data)
{
	unsigned int	render_height;
	unsigned int	y_min;
	unsigned int	y_max;
	int				i;

	i = 0;
	render_height = vp->h / THREAD_NUMBER;
	y_min = 0;
	y_max = render_height;
	while (i < THREAD_NUMBER)
	{
		data[i] = init_single_data(vp, render, aa_data, &simple_ray_trace);
		data[i].x_min = 0;
		data[i].x_max = vp->w;
		data[i].y_min = y_min;
		data[i].y_max = y_max;
		y_min = y_max;
		if (i < THREAD_NUMBER - 2)
			y_max += (render_height + i % 2);
		else
			y_max = vp->h;
		i++;
	}
}
