//
// Created by Jules Cayot on 17/05/2024.
//

#ifndef MINIRT_HOOKS_H
# define MINIRT_HOOKS_H

# include <miniRT.h>

typedef struct	s_switch_cam_hook_param
{
	mlx_t		*mlx;
	t_scene		*render_scene;
	mlx_image_t	**render_images;
}	t_switch_cam_hook_param;

void	close_hook(void *param);
void	add_switch_cam_hook(t_switch_cam_hook_param *param,
							mlx_t *mlx, mlx_image_t **images, t_scene *scene);

int		switch_cam(mlx_t* mlx, mlx_image_t** render_images, t_scene *scene, int cam_i);

#endif //MINIRT_HOOKS_H
