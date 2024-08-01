//
// Created by jcayot on 7/22/24.
//

#include <mlx_utils.h>

t_rgb	get_pixel_color(void *address)
{
	t_rgb	color;

	color.r = (int) *((uint8_t *) address);
	color.g = (int) *((uint8_t *) address + sizeof (uint8_t));
	color.b = (int) *((uint8_t *) address + (2 * sizeof (uint8_t)));
	return (color);
}
