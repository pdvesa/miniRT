/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_scene.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcayot <jcayot.student@hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 20:30:53 by jcayot            #+#    #+#             */
/*   Updated: 2024/07/18 20:30:54 by jcayot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT_render.h>

t_viewport	init_viewport(t_camera *camera, uint32_t width, uint32_t height)
{
	t_viewport	viewport;

	viewport.w = width;
	viewport.h = height;
	viewport.cam = camera;
	viewport.cam_scalar = cosf((float)(camera->fov / 2) * (M_PI / 180.f));
	viewport.v_right = cross_product((t_vector){0, 1, 0}, camera->vector);
	viewport.v_up = cross_product(camera->vector, viewport.v_right);
	return (viewport);
}

t_render_data	init_single_data(t_scene *scene, t_viewport *vp, void *render)
{
	t_render_data	data;

	data.scene = scene;
	data.viewport = vp;
	data.render = render;
	data.x_min = 0;
	data.x_max = vp->w;
	data.y_min = 0;
	data.y_max = vp->h;
	return (data);
}

void	ray_trace(t_scene *scene, mlx_image_t *image)
{
	t_viewport		viewport;
	t_render_data	single_data;

	viewport = init_viewport(scene->camera, image->width, image->height);
	if (THREAD_NUMBER > 1 && THREAD_NUMBER <= HEIGHT)
	{
		if (multi_thread_render(scene, &viewport, image->pixels))
			return ;
	}
	ft_putendl_fd("MiniRT single thread render", 1);
	single_data = init_single_data(scene, &viewport, image->pixels);
	render_thread(&single_data);
}
