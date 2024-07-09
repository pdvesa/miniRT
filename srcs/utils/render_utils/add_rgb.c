//
// Created by jules on 08/06/2024.
//

#include <render_utils.h>

t_rgb	add_rgb(t_rgb rgb1, t_rgb rgb2)
{
	t_rgb	result;

	result.r = 255 - sqrt((pow(255-rgb1.r, 2) + pow(255-rgb2.r, 2))/2);
	result.g = 255 - sqrt((pow(255-rgb1.g, 2) + pow(255-rgb2.g, 2))/2);
	result.b = 255 - sqrt((pow(255-rgb1.b, 2) + pow(255-rgb2.b, 2))/2);
	return (result);
}
