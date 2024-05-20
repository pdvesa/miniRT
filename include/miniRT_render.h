//
// Created by Jules Cayot on 5/18/24.
//

#ifndef MINIRT_RENDER_H
# define MINIRT_RENDER_H

# include <miniRT.h>

void			ray_trace(mlx_image_t *image, t_render_scene *scene, int cam_index);
t_coordinates	get_closer_inter(t_render_scene *scene, int cam_index, unsigned int w, unsigned int h);

#endif //MINIRT_RENDER_H
