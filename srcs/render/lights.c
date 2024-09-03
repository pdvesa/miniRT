/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lights.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcayot <jcayot.student@hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 20:22:18 by jcayot            #+#    #+#             */
/*   Updated: 2024/07/18 20:22:20 by jcayot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT_render.h>

float	get_light_coef(t_vector vect_to_light, t_vector normal_inter)
{
	float	light_coef;

	light_coef = dot_product(vect_to_light, normal_inter);
	if (light_coef < 0.0f)
		light_coef *= -1.0f;
	return (light_coef);
}

t_rgb	reflective_light(t_scene *scene, t_ray *ray, void *obj, int obj_type)
{
	t_rgb	color;
	float	reflection_coef;
	t_ray	indirect_ray;

	color = (t_rgb){0, 0, 0};
	indirect_ray.line.origin = ray->inter.point;
	indirect_ray.line.direction = normalize_vector(
		vect_from_points(ray->inter.point, get_obj_coordinates(obj, obj_type)));
	indirect_ray.inter = get_closer_inter(&indirect_ray.line, scene);
	if (indirect_ray.inter.object != obj)
		return (color);
	reflection_coef = get_light_coef(indirect_ray.line.direction,
		get_normal_to_inter(ray)) * get_obj_reflectivity(obj, obj_type);
	color = combine_rgb(get_diffuse_light(scene, &indirect_ray),
		get_object_color(obj, obj_type));
	color = scalar_rgb(color, reflection_coef);
	return (color);
}

t_rgb	get_specular_light(t_scene *scene, t_ray *ray)
{
	t_rgb	specular;
	int		i;

	specular = (t_rgb){0, 0, 0};
	i = 0;
	while (scene->sphere[i])
		specular = add_rgb(specular, reflective_light(scene, ray,
			scene->sphere[i++], sp));
	i = 0;
	while (scene->plane[i])
		specular = add_rgb(specular, reflective_light(scene, ray,
			scene->plane[i++], pl));
	i = 0;
	while (scene->cylinder[i])
		specular = add_rgb(specular, reflective_light(scene, ray,
			scene->cylinder[i++], cyka));
	return (specular);
}

t_rgb	get_diffuse_light(t_scene *scene, t_ray *ray)
{
	t_rgb	color;
	float	light_coef;
	t_line	inter_to_dest;
	t_inter	closer_inter;

	inter_to_dest.origin = ray->inter.point;
	inter_to_dest.direction = normalize_vector(
		vect_from_points(ray->inter.point, scene->light->center));
	closer_inter = get_closer_inter(&inter_to_dest, scene);
	if (closer_inter.object
			&& point_distance(ray->inter.point, closer_inter.point) <
			point_distance(ray->inter.point, scene->light->center))
		return ((t_rgb) {0, 0, 0});
	light_coef = get_light_coef(inter_to_dest.direction,
		get_normal_to_inter(ray)) * scene->light->brightness;
	color = scalar_rgb(get_object_color(ray->inter.object, ray->inter.object_type),
		light_coef);
	return (color);
}

t_rgb	get_ambiant_light(t_ambient_light *am_light, t_ray *ray)
{
	t_rgb	color;

	color = scalar_rgb(am_light->rgb, am_light->ratio);
	if (ray->inter.object)
		color = combine_rgb(color, get_object_color(ray->inter.object,
			ray->inter.object_type));
	return (color);
}
