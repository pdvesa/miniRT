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

t_rgb	calculate_color(t_scene *scene, t_viewport *viewport, t_pixel_cdts *p)
{
	t_ray	ray;
	t_rgb	ambient_light;
	t_rgb	diffuse_lights;
	t_rgb	object_color;

	ray = ray_to_object(scene, viewport, p);
	if (ray.inter.object)
	{
		object_color = get_object_color(&ray);
		ambient_light = get_ambient_light(scene->ambient_light, &object_color);
		diffuse_lights = inter_to_light(scene, &ray, &object_color);
		return (add_rgb(ambient_light, diffuse_lights));
	}
	return (get_ambient_light(scene->ambient_light, NULL));
}

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
