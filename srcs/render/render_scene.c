//
// Created by Jules Cayot on 5/18/24.
//

#include <miniRT_render.h>

t_viewport	initialise_viewport(mlx_image_t *image, t_camera *camera)
{
	t_viewport	viewport;

	viewport.w = image->width;
	viewport.h = image->height;
	viewport.cam = camera;
	viewport.v_up = orthogonal_vector(camera->vector, .0f, 1.0f);
	viewport.v_right = cross_product(camera->vector, viewport.v_up);
	return (viewport);
}

void	set_pixel_color(void *address, u_int8_t r, u_int8_t g, u_int8_t b)
{
	ft_memset(address, r, sizeof (int8_t));
	ft_memset(address + sizeof (u_int8_t), g, sizeof (int8_t));
	ft_memset(address + 2 * sizeof (u_int8_t), b, sizeof (int8_t));
	ft_memset(address + 3 * sizeof (u_int8_t), 255, sizeof (int8_t));
}

t_rgb	calculate_color(t_scene *scene, t_viewport *viewport, t_pixel_cdts *p)
{
	t_ray	ray;
	t_rgb	ambient_light;
	t_rgb	diffuse_lights;
	t_rgb	sum_lights;

	ray = ray_to_object(scene, viewport, p);
	ambient_light = get_ambient_light(scene->ambient_light);
	if (ray.inter_point.object)
	{
		diffuse_lights = inter_to_light(scene, &ray);
		sum_lights = add_rgb(diffuse_lights, ambient_light);
	}
	else
		sum_lights = ambient_light;
	return (sum_lights);
}

void	ray_trace(mlx_image_t *image, t_scene *scene)
{
	t_pixel_cdts	pixel;
	t_viewport		viewport;
	t_rgb 			color;
	void			*address;

	pixel.x = 0;
	pixel.y = 0;
	viewport = initialise_viewport(image, scene->camera);
	while (pixel.y < viewport.h)
	{
		pixel.x = 0;
		while (pixel.x < viewport.w)
		{
			color = calculate_color(scene, &viewport, &pixel);
			address = image -> pixels + (((pixel.y * image -> width) + (pixel.x)) * sizeof (uint32_t));
			set_pixel_color(address, color.r, color.g, color.b);
			pixel.x++;
		}
		pixel.y++;
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
	mlx_loop(mlx);
	mlx_delete_image(mlx, render_image);
	return (EXIT_SUCCESS);
}
