/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_viewport.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcayot <jcayot.student@hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 14:47:22 by jcayot            #+#    #+#             */
/*   Updated: 2024/08/13 14:47:24 by jcayot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT_render.h>

t_vp	init_viewport(t_scene *scene, uint32_t width, uint32_t height)
{
	t_vp	viewport;

	viewport.w = width;
	viewport.h = height;
	viewport.scene = scene;
	viewport.cam_scalar = cosf(((float) scene->cam->fov / 2.f)
			* ((float) M_PI / 180.f));
	viewport.v_right = cross_product((t_vector){0, 1, 0},
			scene->cam->vect);
	viewport.v_up = cross_product(scene->cam->vect, viewport.v_right);
	return (viewport);
}

t_vp	init_super_vp(t_vp *vp)
{
	t_vp	super_vp;

	super_vp.w = vp->w * MSAA_FACTOR;
	super_vp.h = vp->h * MSAA_FACTOR;
	return (super_vp);
}
