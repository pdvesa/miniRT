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

int light_visible(t_scene *scene, t_ray *ray, t_coordinates light)
{
	t_line			line;
	t_inter_point	closer_inter;
	float			light_distance;
	float			inter_distance;

	line.origin = ray->inter_point.coordinates;
	line.direction = vector_from_points(ray->inter_point.coordinates, light);
	closer_inter = get_closer_inter(&line, scene, ray->inter_point.object);
	if (closer_inter.object == NULL)
		return (1);
	inter_distance = point_distance(ray->inter_point.coordinates, closer_inter.coordinates);
	light_distance = point_distance(ray->inter_point.coordinates, light);
	if (inter_distance < light_distance)
		return (0);
	return (1);
}

t_rgb inter_to_light(t_scene* scene, t_ray* ray)
{
	t_rgb	color;
	t_vector	light_dir;
	t_vector	normal_to_inter;
	float		light_coefficient;

	color.r = 0;
	color.g = 0;
	color.b = 0;
	if (light_visible(scene, ray, scene->light->center))
	{
		light_dir = vector_from_points(scene->light->center, ray->inter_point.coordinates);
		light_dir = normalize_vector(light_dir);
		normal_to_inter = get_normal_to_inter(ray);
		light_coefficient = dot_product(light_dir, normal_to_inter) * scene->light->brightness;
		color = get_object_color(ray);
		color.r *= light_coefficient;
		color.g *= light_coefficient;
		color.b *= light_coefficient;
	}
	return (color);
}

t_rgb	get_ambient_light(t_ambient_light *am_light)
{
	t_rgb	am_light_color;

	am_light_color.r = am_light->rgb.r * am_light->ratio;
	am_light_color.g = am_light->rgb.g * am_light->ratio;
	am_light_color.b = am_light->rgb.b * am_light->ratio;
	return (am_light_color);
}
