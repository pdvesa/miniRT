//
// Created by jules on 08/06/2024.
//

#include <miniRT_utils.h>

t_rgb	add_rgb(t_rgb rgb1, t_rgb rgb2)
{
	t_rgb	result;

	result.r = rgb1.r + rgb2.r;
	if (result.r > 255)
		result.r = 255;
	result.g = rgb1.g + rgb2.g;
	if (result.g > 255)
		result.g = 255;
	result.b = rgb1.b + rgb2.b;
	if (result.b > 255)
		result.b = 255;
	return (result);
}
