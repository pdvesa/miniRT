//
// Created by jules on 20/07/2024.
//

#include <miniRT_render.h>

void	*render_thread(void *data_ptr)
{
	t_render_data	*data;
	t_pixel_cdts	p;
	t_rgb			color;

	data = (t_render_data *) data_ptr;
	p.y = data->y_min;
	while (p.y < data->y_max)
	{
		p.x = data->x_min;
		while (p.x < data->x_max)
		{
			color = calculate_color(data->scene, data->viewport, &p);
			set_pixel_color(data->render + (((p.y * data->viewport->w) + (p.x))
					* sizeof (uint32_t)), color.r, color.g, color.b);
			p.x++;
		}
		p.y++;
	}
	return (NULL);
}
