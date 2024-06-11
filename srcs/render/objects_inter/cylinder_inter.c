//
// Created by jules on 11/06/2024.
//

#include <render_inter.h>

t_inter_point	cylinder_inter(t_line *line, t_cylinder *cylinder)
{
	t_inter_point	inter;

	inter.coordinates = new_far_point();
	inter.object_type = cyka;
	inter.object = cylinder;
}
