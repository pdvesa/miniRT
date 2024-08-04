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

void	do_full_ray_trace(mlx_image_t *image, t_vp *vp, t_msaa_data *mssa_data)
{
	t_render_data	single_data;

	if (THREAD_NUMBER > 1 && THREAD_NUMBER <= HEIGHT)
	{
		if (multi_thread_render(vp, image->pixels, mssa_data))
			return ;
	}
	ft_putendl_fd("MiniRT single thread render", 1);
	single_data = init_single_data(vp, image->pixels, mssa_data, &simple_ray_trace);
	render_thread(&single_data);
}

void	do_msaa(mlx_image_t *image, t_vp *vp, t_msaa_data *mssa_data)
{
	t_render_data	render_data;

	render_data = init_single_data(vp, image->pixels, mssa_data, &objs_bounds_ray_trace);
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
