//
// Created by jcayot on 7/22/24.
//

#include <mlx_utils.h>

t_rgb	get_pixel_color(void *address)
{
	t_rgb	color;

	color = *((t_rgb*) address);
	return (color);
}
