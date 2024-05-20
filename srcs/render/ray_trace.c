//
// Created by Jules Cayot on 5/20/24.
//

#include <miniRT_render.h>

int	calculate_color(t_render_scene *scene, int cam_index, unsigned int w, unsigned int h)
{

}

void	ray_trace(mlx_image_t *image, t_render_scene *scene, int cam_index)
{
	unsigned int	w;
	unsigned int	h;
	int 			pixel_color;

	w = 0;
	h = 0;
	while (h < image -> height)
	{
		while (w < image -> width)
		{
			pixel_color = calculate_color(scene, cam_index, w, h);
			w++;
		}
		h++;
	}
}
