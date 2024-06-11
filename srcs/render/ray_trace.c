//
// Created by Jules Cayot on 5/20/24.
//

#include <miniRT_render.h>

int	calculate_color(t_scene *scene, int cam_i, t_image_size s, t_pixel_cdts p)
{
	int		color;
	t_ray	ray;
	t_rgb	ambient_light;
	t_rgb	diffuse_lights;
	t_rgb	sum_lights;

	ray = ray_to_object(scene, cam_i, s, p);
	ambient_light = get_ambient_light(*scene->ambient_light);
	diffuse_lights = ray_to_lights(scene->light, &ray);
	sum_lights = add_rgb(ambient_light, diffuse_lights);
	color = get_color_int(sum_lights.r, sum_lights.g, sum_lights.b, 1);
	return (color);
}

void	ray_trace(mlx_image_t *image, t_scene *scene, int cam_index)
{
	t_pixel_cdts	pixel;
	t_image_size	size;
	int 			color;
	void			*address;

	pixel.x = 0;
	pixel.y = 0;
	size.W = image -> width;
	size.H = image -> height;
	while (pixel.y < size.H)
	{
		while (pixel.x < size.W)
		{
			color = calculate_color(scene, cam_index, size, pixel);
			address = image -> pixels + (pixel.y * image -> width) + pixel.x;
			ft_memset(address, color, sizeof (int));
			pixel.x++;
		}
		pixel.y++;
	}
}
