//
// Created by jules on 08/06/2024.
//

#include "mlx_utils.h"

int get_color_int(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}
