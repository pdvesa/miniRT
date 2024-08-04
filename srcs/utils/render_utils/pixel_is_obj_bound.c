//
// Created by jules on 03/08/2024.
//

#include <miniRT_render.h>

int	pixel_is_obj_bound(t_msaa_data *msaa_data, t_pxl_cdts *p, t_vp *vp)
{
	if (p->x > 0 && msaa_data[((p->y * vp->w) + p->x)].object
					!= msaa_data[((p->y * vp->w) + (p->x - 1))].object)
		return (1);
	if (p->x < vp->w - 1 && msaa_data[((p->y * vp->w) + p->x)].object
							!= msaa_data[((p->y * vp->w) + (p->x + 1))].object)
		return (1);
	if (p->y > 0 && msaa_data[((p->y * vp->w) + p->x)].object
					!= msaa_data[(((p->y - 1) * vp->w) + p->x)].object)
		return (1);
	if (p->y < vp->h - 1 && msaa_data[((p->y * vp->w) + p->x)].object
							!= msaa_data[(((p->y + 1) * vp->w) + p->x)].object)
		return (1);
	return (0);
}
