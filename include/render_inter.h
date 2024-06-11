//
// Created by jules on 11/06/2024.
//

#ifndef RENDER_INTER_H
# define RENDER_INTER_H

# include <miniRT_render.h>

t_inter_point	sphere_inter(t_line *line, t_sphere *sphere);
t_inter_point	plane_inter(t_line *line, t_plane *plan);
t_inter_point	cylinder_inter(t_line *line, t_cylinder *cylinder);
t_vector		get_normal_to_inter(t_ray *ray);

#endif //RENDER_INTER_H
