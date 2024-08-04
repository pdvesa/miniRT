//
// Created by jules on 03/08/2024.
//

#include <miniRT_render.h>

void	multi_render_data(t_render_data *data, t_vp *vp, void *render, t_msaa_data *msaa_data)
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
		data[i].vp = vp;
		data[i].msaa_data = msaa_data;
		data[i].render = render;
		data[i].x_min = 0;
		data[i].x_max = vp->w;
		data[i].y_min = y_min;
		data[i].y_max = y_max;
		y_min = y_max;
		if (i < THREAD_NUMBER - 1)
			y_max += render_height;
		else
			y_max = vp->h;
		data[i].render_f = &simple_ray_trace;
		i++;
	}
}

t_render_data init_single_data(t_vp* vp, void* render, t_msaa_data *msaa_data)
{
	t_render_data	data;

	data.vp = vp;
	data.msaa_data = msaa_data;
	data.render = render;
	data.x_min = 0;
	data.x_max = vp->w;
	data.y_min = 0;
	data.y_max = vp->h;
	data.render_f = &simple_ray_trace;
	return (data);
}
