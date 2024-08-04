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

t_vp	init_viewport(t_scene *scene, uint32_t width, uint32_t height)
{
	t_vp	viewport;

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

void	do_full_ray_trace(mlx_image_t *image, t_vp *vp, t_msaa_data *mssa_data)
{
	t_render_data	single_data;

	if (THREAD_NUMBER > 1 && THREAD_NUMBER <= HEIGHT)
	{
		if (multi_thread_render(vp, image->pixels, mssa_data))
			return ;
	}
	ft_putendl_fd("MiniRT single thread render", 1);
	single_data = init_single_data(vp, image->pixels, mssa_data);
	render_thread(&single_data);
}

void	do_msaa(mlx_image_t *image, t_vp *vp, t_msaa_data *mssa_data)
{
	t_render_data	render_data;

	render_data = init_single_data(vp, image->pixels, mssa_data);
	render_data.render_f = &objs_bounds_ray_trace;
	render_thread(&objs_bounds_ray_trace);
}

int	render_scene(t_scene *scene, mlx_image_t *image)
{
	t_vp		vp;
	t_msaa_data	*msaa_data;

	vp = init_viewport(scene, image->width, image->height);
	msaa_data = malloc(image->width * image->height * sizeof (t_msaa_data));
	do_full_ray_trace(image, &vp ,msaa_data);
	if (msaa_data)
	{
		do_msaa(image, &vp, msaa_data);
		free(msaa_data);
	}
	return (EXIT_SUCCESS);
}
