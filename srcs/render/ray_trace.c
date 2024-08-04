//
// Created by jules on 03/08/2024.
//

#include <miniRT_render.h>

t_rgb	ray_trace_pixel(t_vp *vp, t_pxl_cdts *p, t_msaa_data *msaa_data)
{
	t_ray	ray;
	t_rgb	ambient_light;
	t_rgb	diffuse_lights;
	t_rgb	object_color;

	ray = ray_to_object(vp, p);
	if (msaa_data)
		msaa_data->object = ray.inter.object;
	if (ray.inter.object)
	{
		object_color = get_object_color(&ray);
		ambient_light = get_ambient_light(vp->scene->ambient_light, &object_color);
		diffuse_lights = inter_to_light(vp->scene, &ray, &object_color,
										&msaa_data->light_visible);
		return (add_rgb(ambient_light, diffuse_lights));
	}
	else
		return (get_ambient_light(vp->scene->ambient_light, NULL));
}

void	simple_ray_trace(t_vp *vp, t_pxl_cdts *p, t_msaa_data *msaa_data, void *pxl_addr)
{
	t_rgb	color;

	color = ray_trace_pixel(vp, p, msaa_data);
	set_pixel_color(pxl_addr, &color);
}

void	objs_bounds_ray_trace(t_vp* vp, t_pxl_cdts *p, t_msaa_data *msaa_data, void *pxl_addr)
{
	static t_vp	super_vp;
	t_rgb		color;
	t_rgb		colors[MSAA_FACTOR];
	int			n;
	t_pxl_cdts	super_p;

	if (pixel_is_obj_bound(msaa_data, p, vp))
	{
		super_vp = init_super_vp(vp);
		n = 0;
		super_p.y = p->y * MSAA_FACTOR;
		while (super_p.y < (p->y * MSAA_FACTOR) + MSAA_FACTOR)
		{
			super_p.x = p->x * MSAA_FACTOR;
			while (super_p.x < (p->x * MSAA_FACTOR) + MSAA_FACTOR)
			{
				colors[n] = ray_trace_pixel(&super_vp, &super_p, msaa_data);
				n++;
				super_p.x++;
			}
			super_p.y++;
		}
		color = average_rgb(colors, n);
		set_pixel_color(pxl_addr, &color);
	}
}
