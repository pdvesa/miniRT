//
// Created by jules on 09/07/2024.
//

#include <mlx_utils.h>

void	set_pixel_color(void *address, u_int8_t r, u_int8_t g, u_int8_t b)
{
	ft_memset(address, r, sizeof (int8_t));
	ft_memset(address + sizeof (u_int8_t), g, sizeof (int8_t));
	ft_memset(address + 2 * sizeof (u_int8_t), b, sizeof (int8_t));
	ft_memset(address + 3 * sizeof (u_int8_t), 255, sizeof (int8_t));
}
