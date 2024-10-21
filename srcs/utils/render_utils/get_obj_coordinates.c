/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_obj_coordinates.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcayot <jcayot.student@hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 21:05:34 by jcayot            #+#    #+#             */
/*   Updated: 2024/07/18 21:05:35 by jcayot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT_render.h>

t_coordinates	get_obj_coordinates(void *obj, int obj_type)
{
	if (obj_type == sp)
		return (((t_sphere *)(obj))->center);
	if (obj_type == pl)
		return (((t_plane *)(obj))->coordinates);
	if (obj_type == cyka || obj_type == cyka_circle)
		return (((t_cylinder *)(obj))->center);
	return ((t_coordinates){0.f, 0.f, 0.f});
}
