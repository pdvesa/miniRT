/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_trace.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcayot <jcayot.student@hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 14:46:48 by jcayot            #+#    #+#             */
/*   Updated: 2024/08/13 14:46:51 by jcayot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT_render.h>

t_rgb	ray_trace_pixel(t_vp *vp, t_pxl_cdts *p, t_aa_data *aa_data)
{
	t_rgb	pixel_color;
	t_ray	ray;
	t_rgb	ambient_light;
	t_rgb	diffuse_lights;
	t_rgb	specular_lights;
	t_rgb	object_color;

	ray = ray_to_object(vp, p);
	if (aa_data)
		aa_data->object = ray.inter.object;
	if (!ray.inter.object)
		return (get_ambiant_light(vp->scene->am_light, NULL));
	object_color = get_object_color(ray.inter.object, ray.inter.object_type);
	ambient_light = get_ambiant_light(vp->scene->am_light, &object_color);
	diffuse_lights = get_diffuse_light(vp->scene, &ray, &object_color);
	specular_lights = get_specular_light(vp->scene, &ray, &object_color);
	pixel_color = add_rgb(ambient_light, diffuse_lights);
	pixel_color = add_rgb(pixel_color, specular_lights);
	return (pixel_color);
}

void	simple_ray_trace(t_vp *vp, t_pxl_cdts *p, t_aa_data *aa_data,
			void *pxl_addr)
{
	t_rgb	color;

	color = ray_trace_pixel(vp, p, aa_data);
	set_pixel_color(pxl_addr, &color);
}

void	objs_bounds_ray_trace(t_vp *vp, t_pxl_cdts *p, t_aa_data *aa_data,
			void *pxl_addr)
{
	static t_vp	super_vp;
	t_rgb		color;
	t_rgb		colors[MSAA_FACTOR];
	int			n;
	t_pxl_cdts	super_p;

	if (pixel_is_obj_bound(aa_data, p, vp))
	{
		super_vp = init_super_vp(vp);
		n = 0;
		super_p.y = p->y * MSAA_FACTOR;
		while (super_p.y < (p->y * MSAA_FACTOR) + MSAA_FACTOR)
		{
			super_p.x = p->x * MSAA_FACTOR;
			while (super_p.x < (p->x * MSAA_FACTOR) + MSAA_FACTOR)
			{
				colors[n] = ray_trace_pixel(&super_vp, &super_p, aa_data);
				n++;
				super_p.x++;
			}
			super_p.y++;
		}
		color = average_rgb(colors, n);
		set_pixel_color(pxl_addr, &color);
	}
}
