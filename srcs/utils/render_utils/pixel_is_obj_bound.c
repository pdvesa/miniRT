/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixel_is_obj_bound.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcayot <jcayot.student@hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 14:56:09 by jcayot            #+#    #+#             */
/*   Updated: 2024/08/13 14:56:18 by jcayot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT_render.h>

int	pixel_is_obj_bound(t_aa_data *aa_data, t_pxl_cdts *p, t_vp *vp)
{
	if (p->x > 0 && aa_data[((p->y * vp->w) + p->x)].object
		!= aa_data[((p->y * vp->w) + (p->x - 1))].object)
		return (1);
	if (p->x < vp->w - 1 && aa_data[((p->y * vp->w) + p->x)].object
		!= aa_data[((p->y * vp->w) + (p->x + 1))].object)
		return (1);
	if (p->y > 0 && aa_data[((p->y * vp->w) + p->x)].object
		!= aa_data[(((p->y - 1) * vp->w) + p->x)].object)
		return (1);
	if (p->y < vp->h - 1 && aa_data[((p->y * vp->w) + p->x)].object
		!= aa_data[(((p->y + 1) * vp->w) + p->x)].object)
		return (1);
	return (0);
}
