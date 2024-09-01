//
// Created by jules on 01/09/2024.
//

#include <miniRT_render.h>

t_rgb	combine_rgb(t_rgb rgb1, t_rgb rgb2)
{
	t_rgb	rgb;

	rgb.r = (int) ((((float) rgb1.r / 255.f) * (float) rgb2.r / 255.f) * 255.f);
	rgb.g = (int) ((((float) rgb1.g / 255.f) * (float) rgb2.g / 255.f) * 255.f);
	rgb.b = (int) ((((float) rgb1.b / 255.f) * (float) rgb2.b / 255.f) * 255.f);
	return (rgb);
}
