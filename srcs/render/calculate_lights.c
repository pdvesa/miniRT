//
// Created by jules on 06/06/2024.
//

#include <miniRT_render.h>

t_rgb get_object_color(t_ray *ray)
{
	if (ray->inter_point.object_type == sp)
		return (((t_sphere*)(ray->inter_point.object))->rgb);
	else if (ray->inter_point.object_type == pl)
		return (((t_plane*)(ray->inter_point.object))->rgb);
	else
		return (((t_cylinder*)(ray->inter_point.object))->rgb);
}

t_rgb	diffuse_light(t_light *light, t_ray *ray)
{
	t_rgb		color;
	t_vector	light_dir;
	t_vector	normal_to_inter;
	float		light_coefficient;

	light_dir = vector_from_points(light->center, ray->inter_point.coordinates);
	light_dir = normalize_vector(light_dir);
	normal_to_inter = calculate_normal_inter(ray);
	light_coefficient = dot_product(light_dir, normal_to_inter) * light -> brightness;
	color = get_object_color(ray);
	color.r *= light_coefficient;
	color.g *= light_coefficient;
	color.b *= light_coefficient;
	return (color);
}

t_rgb	get_diffuse_lights(t_light **lights, t_ray *ray)
{
	t_rgb	color_sum;
	t_rgb	color;
	int		i;

	i = 0;
	color_sum.r = 0;
	color_sum.g = 0;
	color_sum.b = 0;
	while (lights[i])
	{
		color = diffuse_light(lights[i], ray);
		color_sum = add_rgb(color_sum, color);
		i++;
	}
	return (color_sum);
}

t_rgb	get_ambient_light(t_ambient_light *am_light)
{
	t_rgb	am_light_color;

	am_light_color.r = am_light->rbg.r * am_light->ratio;
	am_light_color.g = am_light->rbg.g * am_light->ratio;
	am_light_color.b = am_light->rbg.b * am_light->ratio;
	return (am_light_color);
}
