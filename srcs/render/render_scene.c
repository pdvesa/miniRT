/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_scene.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcayot <jcayot.student@hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 20:30:53 by jcayot            #+#    #+#             */
/*   Updated: 2024/07/18 20:30:54 by jcayot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT_render.h>

t_viewport	init_viewport(t_camera *camera, uint32_t width, uint32_t height)
{
	t_viewport	viewport;

	viewport.w = width;
	viewport.h = height;
	viewport.cam = camera;
	viewport.cam_scalar = cosf((float)(camera->fov / 2) * (M_PI / 180.f));
	viewport.v_right = cross_product((t_vector){0, 1, 0}, camera->vector);
	viewport.v_up = cross_product(camera->vector, viewport.v_right);
	return (viewport);
}

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

void	*ray_trace(t_scene *scene, uint32_t width, uint32_t height)
{
	void			*render;
	t_viewport		viewport;
	t_pixel_cdts	p;
	t_rgb			color;

	render = malloc(width * height * sizeof (uint32_t));
	if (!render)
		return (NULL);
	ft_putendl_fd("MiniRT : Rendering starting", 1);
	viewport = init_viewport(scene->camera, width, height);
	p.x = 0;
	p.y = 0;
	while (p.y < viewport.h)
	{
		p.x = 0;
		while (p.x < viewport.w)
		{
			color = calculate_color(scene, &viewport, &p);
			set_pixel_color(render + (((p.y * width) + (p.x))
					* sizeof (uint32_t)), color.r, color.g, color.b);
			p.x++;
		}
		p.y++;
	}
	return (render);
}
