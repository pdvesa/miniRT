/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_thread.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcayot <jcayot.student@hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/20 14:55:43 by jcayot            #+#    #+#             */
/*   Updated: 2024/07/20 14:55:46 by jcayot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT_render.h>

t_raw_pixel	ray_trace_pixel(t_viewport *vp, t_pixel_cdts *p)
{
	t_raw_pixel	r_pxl;
	t_rgb		ambient_light;
	t_rgb		diffuse_lights;
	t_rgb		object_color;

	r_pxl.ray = ray_to_object(vp, p);
	if (r_pxl . ray.inter.object)
	{
		object_color = get_object_color(&r_pxl.ray);
		ambient_light = get_ambient_light(vp->scene->ambient_light, &object_color);
		diffuse_lights = inter_to_light(vp->scene, &r_pxl, &object_color);
		r_pxl.color = add_rgb(ambient_light, diffuse_lights);
	}
	else
		r_pxl.color = get_ambient_light(vp->scene->ambient_light, NULL);
	return (r_pxl);
}

void	*render_thread(void *data_ptr)
{
	t_render_data	*data;
	t_raw_pixel		*current_raw_pxl;
	t_pixel_cdts	p;

	data = (t_render_data *) data_ptr;
	p.y = data->y_min;
	while (p.y < data->y_max)
	{
		p.x = data->x_min;
		while (p.x < data->x_max)
		{
			current_raw_pxl = data->raw_pixels + (((p.y * data->vp->w) + p.x)
					* sizeof (t_raw_pixel));
			printf("%d, %d \n", p.x, p.y);
			printf("%p\n", current_raw_pxl);
			*current_raw_pxl = ray_trace_pixel(data->vp, &p);
			set_pixel_color(data->render + (((p.y * data->vp->w) + p.x)
					* sizeof (uint32_t)), &current_raw_pxl->color);
			p.x++;
		}
		p.y++;
	}
	return (NULL);
}
