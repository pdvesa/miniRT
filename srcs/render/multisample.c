//
// Created by jules on 29/07/2024.
//

#include <miniRT_render.h>

//int	pixel_is_bound(t_raw_pixel *raw_pixel, uint x, uint y, t_viewport *vp)
//{
//	if (x > 0 && raw_pixel[((y * vp->w) + x)].ray.inter.object
//		!= raw_pixel[((y * vp->w) + (x - 1))].ray.inter.object)
//		return (1);
//	if (x < vp->w - 1 && raw_pixel[((y * vp->w) + x)].ray.inter.object
//		!= raw_pixel[((y * vp->w) + (x + 1))].ray.inter.object)
//		return (1);
//	if (y > 0 && raw_pixel[((y * vp->w) + x)].ray.inter.object
//		!= raw_pixel[(((y - 1) * vp->w) + x)].ray.inter.object)
//		return (1);
//	if (y < vp->h - 1 && raw_pixel[((y * vp->w) + x)].ray.inter.object
//		!= raw_pixel[(((y + 1) * vp->w) + x)].ray.inter.object)
//		return (1);
//	return (0);
//}
//
//t_rgb oversample_obj_bound(t_viewport* vp, uint x, uint y, uint msaa_factor)
//{
//	t_rgb color;
//	return (color);
//}
