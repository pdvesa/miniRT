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

typedef struct s_inter
{
	t_coordinates	point;
	int				object_type;
	void			*object;
}	t_inter;

typedef struct s_ray
{
	t_line			line;
	t_inter			inter;
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

typedef struct s_objs_inter
{
	void	**objects;
	t_inter (*f) (t_line*, void*);
}	t_objs_inter;

t_ray			ray_to_object(t_scene *scene, t_viewport *viewport,
					t_pixel_cdts *p);
t_inter	get_closer_inter(t_line *line, t_scene *scene);
t_rgb			get_ambient_light(t_ambient_light *am_light,
					t_rgb *object_color);
t_rgb			inter_to_light(t_scene *scene, t_ray *ray, t_rgb *object_color);

//render_inter
t_inter	closer_sphere_inter(t_line *line, t_sphere *sphere);
t_inter	plane_inter(t_line *line, t_plane *plan);
t_inter	closer_cylinder_inter(t_line *line, t_cylinder *cylinder);
t_vector		get_normal_to_inter(t_ray *ray);

//self_hide
int				plane_self_hide(t_ray *ray, t_light *light);

# include <render_utils.h>

#endif //MINIRT_RENDER_H
