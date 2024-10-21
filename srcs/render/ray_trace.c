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

	ray = ray_to_object(vp, p, aa_data);
	ambient_light = get_ambiant_light(vp->scene->am_light, &ray);
	if (!ray.inter.object)
		return (ambient_light);
	diffuse_lights = get_diffuse_light(vp->scene, &ray);
	specular_lights = get_specular_light(vp->scene, &ray);
	pixel_color = add_rgb(ambient_light, diffuse_lights);
	pixel_color = add_rgb(specular_lights, pixel_color);
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
	t_rgb		colors[MSAA_FACTOR * 2];
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
				colors[n] = ray_trace_pixel(&super_vp, &super_p, NULL);
				n++;
				super_p.x++;
			}
			super_p.y++;
		}
		color = average_rgb(colors, n);
		set_pixel_color(pxl_addr, &color);
	}
}
