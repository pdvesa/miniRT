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

int light_visible(t_scene *scene, t_coordinates origin, t_coordinates light)
{
	t_line			line;
	t_inter_point	closer_inter;
	float			light_distance;
	float			inter_distance;

	line.origin = origin;
	line.direction = vector_from_points(origin, light);
	closer_inter = get_closer_inter(&line, scene);
	inter_distance = point_distance(origin, closer_inter.coordinates);
	light_distance = point_distance(origin, light);
	if (inter_distance > 0 && inter_distance < light_distance)
		return (0);
	return (1);
}

t_rgb	diffuse_light(t_light *light, t_ray *ray)
{
	t_rgb		color;
	t_vector	light_dir;
	t_vector	normal_to_inter;
	float		light_coefficient;

	light_dir = vector_from_points(light->center, ray->inter_point.coordinates);
	light_dir = normalize_vector(light_dir);
	normal_to_inter = get_normal_to_inter(ray);
	light_coefficient = dot_product(light_dir, normal_to_inter) * light -> brightness;
	color = get_object_color(ray);
	color.r *= light_coefficient;
	color.g *= light_coefficient;
	color.b *= light_coefficient;
	return (color);
}

t_rgb inter_to_lights(t_scene* scene, t_ray* ray)
{
	t_rgb	color_sum;
	t_rgb	color;
	int		i;

	i = 0;
	color_sum.r = 0;
	color_sum.g = 0;
	color_sum.b = 0;
	while (scene->light[i])
	{
		if (light_visible(scene, ray->inter_point.coordinates,
					scene->light[i]->center))
		{
			color = diffuse_light(scene->light[i], ray);
			color_sum = add_rgb(color_sum, color);
		}
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
