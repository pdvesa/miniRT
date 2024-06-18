//
// Created by Jules Cayot on 5/18/24.
//

#ifndef MINIRT_RENDER_H
# define MINIRT_RENDER_H

# include <miniRT.h>
# include <render_inter.h>
# include <render_utils.h>

typedef struct s_inter_point
{
	t_coordinates	coordinates;
	int 			object_type;
	void			*object;
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

typedef struct	s_switch_cam_hook_param
{
	mlx_t		*mlx;
	t_scene		*render_scene;
	mlx_image_t	**render_images;
}	t_switch_cam_hook_param;

int				switch_cam(mlx_t* mlx, mlx_image_t** render_images, t_scene *scene, int cam_i);
void			ray_trace(mlx_image_t *image, t_scene *scene, int cam_index);
t_ray			ray_to_object(t_scene *scene, int cam_i, t_image_size s, t_pixel_cdts p);
t_inter_point	get_closer_inter(t_line *line, t_scene *scene);
t_rgb			get_ambient_light(t_ambient_light *am_light);
t_rgb			inter_to_lights(t_scene* scene, t_ray* ray);

//Hooks
void	add_switch_cam_hook(t_switch_cam_hook_param *param,
							mlx_t *mlx, mlx_image_t **images, t_scene *scene);

//Utils like
t_rgb			add_rgb(t_rgb rgb1, t_rgb rgb2);

#endif //MINIRT_RENDER_H
