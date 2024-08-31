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

t_rgb	get_object_color(void* obj, int obj_type)
{
	if (obj_type == sp)
		return (((t_sphere *) obj)->rgb);
	if (obj_type == pl)
		return (((t_plane *) obj)->rgb);
	if (obj_type == cyka || obj_type == cyka_circle)
		return (((t_cylinder *) obj)->rgb);
	return ((t_rgb){0, 0, 0});
}
