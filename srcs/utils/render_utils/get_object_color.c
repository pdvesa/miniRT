/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_object_color.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcayot <jcayot.student@hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 21:05:34 by jcayot            #+#    #+#             */
/*   Updated: 2024/07/18 21:05:35 by jcayot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT_render.h>

t_rgb	get_object_color(t_ray *ray)
{
	if (ray->inter.object_type == sp)
		return (((t_sphere *)(ray->inter.object))->rgb);
	if (ray->inter.object_type == pl)
		return (((t_plane *)(ray->inter.object))->rgb);
	if (ray->inter.object_type == cyka || ray->inter.object_type == cyka_circle)
		return (((t_cylinder *)(ray->inter.object))->rgb);
	return ((t_rgb){0, 0, 0});
}
