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

void	do_full_ray_trace(mlx_image_t *img, t_vp *vp, t_aa_data *aa_data)
{
	t_render_data	single_data;

	if (THREAD_NUMBER > 1 && THREAD_NUMBER <= HEIGHT)
	{
		if (multi_thread_render(vp, img->pixels, aa_data))
			return ;
	}
	ft_putendl_fd("MiniRT single thread render", 1);
	single_data = init_single_data(vp, img->pixels, aa_data, &simple_ray_trace);
	render_thread(&single_data);
}

void	do_msaa(mlx_image_t *img, t_vp *vp, t_aa_data *aa_data)
{
	t_render_data	render_data;

	render_data = init_single_data(vp, img->pixels, aa_data,
			&objs_bounds_ray_trace);
	render_data.render_f = &objs_bounds_ray_trace;
	render_thread(&render_data);
}

int	render_scene(t_scene *scene, mlx_image_t *image)
{
	t_vp		vp;
	t_aa_data	*aa_data;
	u_long		start_t;
	u_long		end_t;

	vp = init_viewport(scene, image->width, image->height);
	aa_data = malloc(image->width * image->height * sizeof (t_aa_data));
	start_t = get_mst();
	do_full_ray_trace(image, &vp, aa_data);
	if (aa_data)
	{
		// do_msaa(image, &vp, aa_data);
		free(aa_data);
	}
	end_t = get_mst();
	printf("Render done in : %.3f seconds\n",
		(double)(end_t - start_t) / 1000.);
	return (EXIT_SUCCESS);
}
