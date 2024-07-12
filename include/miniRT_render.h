/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT_render.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jcayot <jcayot.student@hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 18:24:52 by jcayot            #+#    #+#             */
/*   Updated: 2024/07/11 18:24:57 by jcayot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_RENDER_H
# define MINIRT_RENDER_H

# include <miniRT.h>

typedef struct s_inter_point
{
	t_coordinates	coordinates;
	int				object_type;
	void			*object;
}	t_inter_point;

typedef struct s_ray
{
	t_line			line;
	t_inter_point	inter_point;
}	t_ray;

typedef struct s_viewport
{
	unsigned int	w;
	unsigned int	h;
	t_vector		v_up;
	t_vector		v_right;
	t_camera		*cam;
}	t_viewport;

typedef struct s_pixel_cdts
{
	unsigned int	x;
	unsigned int	y;
}	t_pixel_cdts;

typedef struct s_hook_data
{
	mlx_t		*mlx;
	t_scene		*scene;
	mlx_image_t	*image;
} t_hook_container;


t_ray			ray_to_object(t_scene *scene, t_viewport *viewport,
					t_pixel_cdts *p);

t_inter_point	get_closer_inter(t_line *line, t_scene *scene, void *self);
t_rgb			get_ambient_light(t_ambient_light *am_light,
					t_rgb *object_color);
t_rgb			inter_to_light(t_scene *scene, t_ray *ray, t_rgb *object_color);
t_viewport		initialise_viewport(mlx_image_t *image, t_camera *camera);

//render_inter
t_inter_point	closer_sphere_inter(t_line *line, t_sphere *sphere);
t_inter_point	plane_inter(t_line *line, t_plane *plan);
t_inter_point	cylinder_inter(t_line *line, t_cylinder *cylinder);
t_vector		get_normal_to_inter(t_ray *ray);

//self_hide
int				sphere_self_hide(t_line *line_to_light, t_ray *ray);
int				plane_self_hide(t_ray *ray, t_light *light);

# include <render_utils.h>

//Hooks
void			key_function(mlx_key_data_t keydata, void *param);

#endif //MINIRT_RENDER_H
