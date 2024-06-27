//
// Created by Jules Cayot on 5/18/24.
//

#include <miniRT_render.h>

int calculate_color(t_scene* scene, t_image_size s, t_pixel_cdts p)
{
	int		color;
	t_ray	ray;
	t_rgb	ambient_light;
	t_rgb	diffuse_lights;
	t_rgb	sum_lights;

	ray = ray_to_object(scene, s, p);
	ambient_light = get_ambient_light(scene->ambient_light);
	if (!is_far_point(ray.inter_point.coordinates)) {
		printf("I'm an object\n");
		diffuse_lights = inter_to_light(scene, &ray);
		sum_lights = add_rgb(ambient_light, diffuse_lights);
		printf("R %d G %d B %d", sum_lights.r, sum_lights.g, sum_lights.b);
	} else
		sum_lights = ambient_light;
	color = get_color_int(sum_lights.r, sum_lights.g, 0, sum_lights.b);
	printf("color int %d\n", color);
	return (color);
}

void ray_trace(mlx_image_t* image, t_scene* scene)
{
	t_pixel_cdts	pixel;
	t_image_size	size;
	int 			color;
	void			*address;

	pixel.x = 0;
	pixel.y = 0;
	size.W = image -> width;
	size.H = image -> height;
	while (pixel.y < size.W)
	{
		pixel.x = 0;
		while (pixel.x < size.H)
		{
			color = calculate_color(scene, size, pixel);
			address = image -> pixels + ((pixel.y * image -> height) * sizeof (int)) + (pixel.x * sizeof (int));
			ft_memset(address, color, sizeof (int));
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
