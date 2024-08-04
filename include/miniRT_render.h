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

# ifndef THREAD_NUMBER
#  define THREAD_NUMBER 20
# endif

# ifndef MSAA_FACTOR
#  define MSAA_FACTOR 2
# endif

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

typedef struct s_msaa_data
{
	void	*object;
	int		light_visible;
}	t_msaa_data;

typedef struct s_viewport
{
	unsigned int	w;
	unsigned int	h;
	t_vector		v_up;
	t_vector		v_right;
	t_scene			*scene;
	float			cam_scalar;
}	t_vp;

typedef struct s_pixel_cdts
{
	unsigned int	x;
	unsigned int	y;
}	t_pxl_cdts;

typedef struct s_render_thread_data
{
	unsigned int	x_min;
	unsigned int	x_max;
	unsigned int	y_min;
	unsigned int	y_max;
	t_vp			*vp;
	t_msaa_data		*msaa_data;
	void			*render;
	void			(*render_f)(t_vp*, t_pxl_cdts*, t_msaa_data*, void*);
}	t_render_data;

void			*render_thread(void *data_ptr);
int				multi_thread_render(t_vp *vp, void *render, t_msaa_data *msaa_data);

//Render data
t_render_data	init_single_data(t_vp* vp, void* render, t_msaa_data* msaa_data,
							   void (* render_f)(t_vp*, t_pxl_cdts*, t_msaa_data*, void*));
void			multi_render_data(t_render_data *data, t_vp *vp, void *render, t_msaa_data *msaa_data);

//Viewport
t_vp			init_viewport(t_scene *scene, uint32_t width, uint32_t height);
t_vp			init_super_vp(t_vp* vp);

//Pixel ray-trace
void			simple_ray_trace(t_vp *vp, t_pxl_cdts *p, t_msaa_data *msaa_data, void *pxl_addr);
void			objs_bounds_ray_trace(t_vp* vp, t_pxl_cdts *p, t_msaa_data *msaa_data, void *pxl_addr);

//Ray-trace
t_ray			ray_to_object(t_vp* vp, t_pxl_cdts* p);
t_inter			get_closer_inter(t_line *line, t_scene *scene);
t_rgb			get_ambient_light(t_ambient_light *am_light, t_rgb *object_color);
t_rgb			inter_to_light(t_scene* scene, t_ray* ray, t_rgb* obj_col, int* light_v);

//render_inter
t_inter			closer_sphere_inter(t_line *line, t_sphere *sphere);
t_inter			plane_inter(t_line *line, t_plane *plan);
t_inter			closer_cylinder_inter(t_line *line, t_cylinder *cylinder);
t_vector		get_normal_to_inter(t_ray *ray);

//self_hide
int				plane_self_hide(t_ray *ray, t_light *light);

//Utils
t_rgb			get_object_color(t_ray *ray);
t_rgb			add_rgb(t_rgb rgb1, t_rgb rgb2);
t_rgb			average_rgb(t_rgb *rgb, u_int n);
void			get_cyka_circles_planes(t_cylinder *cylinder, t_plane *result);
int				pixel_is_obj_bound(t_msaa_data *msaa_data, t_pxl_cdts *p, t_vp *vp);

#endif //MINIRT_RENDER_H
