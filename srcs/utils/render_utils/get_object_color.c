//
// Created by jules on 09/07/2024.
//

#include <render_utils.h>

t_rgb	get_object_color(t_ray *ray)
{
	if (ray->inter.object_type == sp)
		return (((t_sphere*)(ray->inter.object))->rgb);
	else if (ray->inter.object_type == pl)
		return (((t_plane*)(ray->inter.object))->rgb);
	else
		return (((t_cylinder*)(ray->inter.object))->rgb);
}
