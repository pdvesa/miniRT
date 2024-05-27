//
// Created by Jules Cayot on 5/20/24.
//

#include <miniRT_render.h>

t_ray	make_ray(t_scene *scene, int cam_i, t_image_size s, t_pixel_cdts p)
{
	t_ray	ray;

	ray.line.origin = scene->camera[cam_i]->center;
	ray.line.direction = ray_direction(scene->camera[cam_i], s, p);
	ray.inter_point = get_closer_inter(&ray.line, scene);
	return (ray);
}

int	calculate_color(t_scene *scene, int cam_i, t_image_size s, t_pixel_cdts p)
{

}

void	ray_trace(mlx_image_t *image, t_scene *scene, int cam_index)
{
	t_pixel_cdts	current_pixel;
	t_image_size	image_size;
	int 			pixel_color;

	current_pixel.x = 0;
	current_pixel.y = 0;
	image_size.W = image -> width;
	image_size.H = image -> height;
	while (current_pixel.y < image_size.H)
	{
		while (current_pixel.x < image_size.W)
		{
			pixel_color = calculate_color(scene, cam_index, image_size, current_pixel);
			current_pixel.x++;
		}
		current_pixel.y++;
	}
}
