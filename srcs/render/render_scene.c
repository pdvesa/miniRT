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

t_viewport	init_viewport(t_scene *scene, uint32_t width, uint32_t height)
{
	t_viewport	viewport;

	viewport.w = width;
	viewport.h = height;
	viewport.scene = scene;
	viewport.cam_scalar = cosf(((float) scene->cam->fov / 2.f)
			* ((float) M_PI / 180.f));
	viewport.v_right = cross_product((t_vector){0, 1, 0}
			, scene->cam->vect);
	viewport.v_up = cross_product(scene->cam->vect, viewport.v_right);
	return (viewport);
}

t_render_data init_single_data(t_viewport* vp, void* render, t_raw_pixel *r_pxl)
{
	t_render_data	data;

	data.vp = vp;
	data.raw_pixels = r_pxl;
	data.render = render;
	data.x_min = 0;
	data.x_max = vp->w;
	data.y_min = 0;
	data.y_max = vp->h;
	return (data);
}

t_raw_pixel	*ray_trace(t_scene *scene, mlx_image_t *image)
{
	t_raw_pixel		*raw_pixels;
	t_viewport		viewport;
	t_render_data	single_data;

	raw_pixels = malloc(image->width * image->height * sizeof (t_raw_pixel));
	if (!raw_pixels)
		return (NULL);
	printf("%p\n", raw_pixels + (image->width * image->height * sizeof (t_raw_pixel)));
	viewport = init_viewport(scene, image->width, image->height);
	if (THREAD_NUMBER > 1 && THREAD_NUMBER <= HEIGHT)
	{
		if (multi_thread_render(&viewport, image->pixels, raw_pixels))
			return (raw_pixels);
	}
	ft_putendl_fd("MiniRT single thread render", 1);
	single_data = init_single_data(&viewport, image->pixels, raw_pixels);
	render_thread(&single_data);
	return (raw_pixels);
}

int	render_scene(t_scene *scene, mlx_image_t *image)
{
	t_raw_pixel	*raw_pixels;

	raw_pixels = ray_trace(scene, image);
	if (!raw_pixels)
		return (EXIT_FAILURE);
	free(raw_pixels);
	return (EXIT_SUCCESS);
}
