/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcayot <jcayot.student@hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 18:23:12 by jcayot            #+#    #+#             */
/*   Updated: 2024/07/11 18:23:14 by jcayot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_UTILS_H
# define RENDER_UTILS_H

# include <miniRT_render.h>

t_rgb	get_object_color(t_ray *ray);
t_rgb	add_rgb(t_rgb rgb1, t_rgb rgb2);
void	get_cyka_circles_planes(t_cylinder *cylinder, t_plane *result);

#endif //RENDER_UTILS_H
