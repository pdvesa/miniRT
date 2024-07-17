//
// Created by jules on 06/06/2024.
//

#include <miniRT_render.h>

int	hide_itself(t_ray *ray, t_light *light)
{
	if (ray->inter.object_type == pl)
		return (plane_self_hide(ray, light));
	return (0);
}

int	light_visible(t_scene *scene, t_ray *ray)
{
	t_line			inter_to_light;
	t_inter	closer_inter;
	float			light_distance;
	float			inter_distance;

	inter_to_light.origin = ray->inter.point;
	inter_to_light.direction = vector_from_points(ray->inter.point, scene->light->center);
	if (hide_itself(ray, scene->light))
		return (0);
	closer_inter = get_closer_inter(&inter_to_light, scene);
	if (closer_inter.object == NULL)
		return (1);
	inter_distance = point_distance(ray->inter.point, closer_inter.point);
	light_distance = point_distance(ray->inter.point, scene->light->center);
	if (inter_distance < light_distance)
		return (0);
	return (1);
}

t_rgb	inter_to_light(t_scene *scene, t_ray *ray, t_rgb *object_color)
{
	t_rgb		color;
	t_vector	inter_to_light;
	t_vector	normal_to_inter;
	float		light_coefficient;

	color.r = 0;
	color.g = 0;
	color.b = 0;
	if (light_visible(scene, ray))
	{
		inter_to_light = vector_from_points(ray->inter.point, scene->light->center);
		inter_to_light = normalize_vector(inter_to_light);
		normal_to_inter = get_normal_to_inter(ray);
		light_coefficient = dot_product(inter_to_light, normal_to_inter);
		if (light_coefficient < 0.f)
			light_coefficient *= -1.f;
		light_coefficient *= scene->light->brightness;
		color.r = (int) ((float) object_color->r * light_coefficient);
		color.g = (int) ((float) object_color->g * light_coefficient);
		color.b = (int) ((float) object_color->b * light_coefficient);
	}
	return (color);
}

t_rgb	get_ambient_light(t_ambient_light *am_light, t_rgb *object_color)
{
	t_rgb	color;

	if (object_color)
		color = add_rgb(am_light->rgb, *object_color);
	else
		color = am_light->rgb;
	color.r *= am_light->ratio;
	color.g *= am_light->ratio;
	color.b *= am_light->ratio;
	return (color);
}
