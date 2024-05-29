//
// Created by Jules Cayot on 5/18/24.
//

#ifndef MINIRT_RENDER_H
# define MINIRT_RENDER_H

# include <miniRT.h>

typedef struct s_inter_point
{
	t_coordinates	coordinates;
	t_rgb			rgb;
}	t_inter_point;

typedef struct	s_ray
{
	t_line			line;
	t_inter_point	inter_point;
}	t_ray;

typedef struct	s_image_size
{
	unsigned int	W;
	unsigned int	H;
}	t_image_size;

typedef struct	s_pixel_cdts
{
	unsigned int	x;
	unsigned int	y;
}	t_pixel_cdts;

void			ray_trace(mlx_image_t *image, t_scene *scene, int cam_index);
t_vector		ray_direction(t_camera *cam, t_image_size s, t_pixel_cdts p);
t_inter_point get_closer_inter(t_line * line, t_scene * scene);

#endif //MINIRT_RENDER_H
