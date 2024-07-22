//
// Created by jcayot on 7/22/24.
//

#include <miniRT_render.h>

t_rgb	average_rgb(t_rgb *rgb, unsigned int n)
{
	t_rgb			average;
	unsigned int	r;
	unsigned int	g;
	unsigned int	b;
	unsigned int	i;

	i = 0;
	r = 0;
	g = 0;
	b = 0;
	while (i < n)
	{
		r += rgb[i].r;
		g += rgb[i].g;
		b += rgb[i].b;
		i++;
	}
	average.r = r / n;
	average.g = g / n;
	average.b = b / n;
	return (average);
}

t_rgb	manual_aa_pixel(void *pixels, unsigned int x, unsigned int y, unsigned int width, unsigned int heigth)
{
	t_rgb			colors[5];
	unsigned int	n;

	n = 1;
	colors[0] = get_pixel_color(pixels + ((y * width) + x) * sizeof (uint32_t));
	if (x > 0)
		colors[n++] = get_pixel_color(pixels + ((y * width) + (x - 1)) * sizeof (uint32_t));
	if (x < width - 1)
		colors[n++] = get_pixel_color(pixels + ((y * width) + (x + 1)) * sizeof (uint32_t));
	if (y > 0)
		colors[n++] = get_pixel_color(pixels + (((y - 1) * width) + x) * sizeof (uint32_t));
	if (y < heigth - 1)
		colors[n++] = get_pixel_color(pixels + (((y + 1) * width) + x) * sizeof (uint32_t));
	return (average_rgb(colors, n));
}

int	manual_anti_aliasing(void *pixels, unsigned int width, unsigned int heigth)
{
	unsigned int	x;
	unsigned int	y;
	void			*old_pixels;
	t_rgb			color;

	old_pixels = malloc(width * heigth * sizeof (uint32_t));
	if (!old_pixels)
		return (0);
	ft_memcpy(old_pixels, pixels, width * heigth * sizeof (uint32_t));
	y = 0;
	while (y < heigth)
	{
		x = 0;
		while (x < width)
		{
			color = manual_aa_pixel(old_pixels, x, y, width, heigth);
			set_pixel_color(pixels + (((y * width) + (x)) * sizeof (uint32_t)),
				color.r, color.g, color.b);
			x++;
		}
		y++;
	}
	free(old_pixels);
	return (1);
}
