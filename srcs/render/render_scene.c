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

#include <miniRT_trans.h>
#include <miniRT_render.h>
#include <miniRT.h>

t_viewport	initialise_viewport(mlx_image_t *image, t_camera *camera)
{
	t_viewport	viewport;

	viewport.w = image->width;
	viewport.h = image->height;
	viewport.cam = camera;
	viewport.cam_scalar = cosf((float)(camera->fov / 2) * (M_PI / 180.f));
	viewport.v_right = cross_product((t_vector){0, 1, 0}, camera->vector);
	viewport.v_up = cross_product(camera->vector, viewport.v_right);
	return (viewport);
}

t_rgb	calculate_color(t_scene *scene, t_viewport *viewport, t_pixel_cdts *p)
{
	t_ray	ray;
	t_rgb	ambient_light;
	t_rgb	diffuse_lights;
	t_rgb	object_color;

	ray = ray_to_object(scene, viewport, p);
	if (ray.inter.object)
	{
		object_color = get_object_color(&ray);
		ambient_light = get_ambient_light(scene->ambient_light, &object_color);
		diffuse_lights = inter_to_light(scene, &ray, &object_color);
		return (add_rgb(ambient_light, diffuse_lights));
	}
	return (get_ambient_light(scene->ambient_light, NULL));
}

void	ray_trace(mlx_image_t *img, t_scene *scene)
{
	t_pixel_cdts	p;
	t_viewport		viewport;
	t_rgb			color;
	void			*address;

	p.x = 0;
	p.y = 0;
	viewport = initialise_viewport(img, scene->camera);
	while (p.y < viewport.h)
	{
		p.x = 0;
		while (p.x < viewport.w)
		{
			color = calculate_color(scene, &viewport, &p);
			address = img -> pixels + (((p.y * img -> width) + (p.x))
					* sizeof (uint32_t));
			set_pixel_color(address, color.r, color.g, color.b);
			p.x++;
		}
		p.y++;
	}
}

int	render_scene(mlx_t *mlx, t_scene *scene)
{
	mlx_image_t				*render_image;

	render_image = mlx_new_image(mlx, mlx -> width, mlx -> height);
	if (!render_image)
		return (ft_putmlx_error());
	ray_trace(render_image, scene);
	if (mlx_image_to_window(mlx, render_image, 0, 0) == -1)
	{
		mlx_delete_image(mlx, render_image);
		return (ft_putmlx_error());
	}
	hook_data.mlx = mlx;
	hook_data.scene = scene;
	hook_data.image = render_image;
	printf("If you want to modify objects press O, for camera C and for light L\n");
//	mlx_resize_hook(mlx, &resize_function, &hook_data);
	mlx_key_hook(mlx, &key_function, &hook_data);
	mlx_loop(mlx);
	mlx_delete_image(mlx, render_image);
	return (EXIT_SUCCESS);
}
