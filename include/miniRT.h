//
// Created by Jules Cayot on 13/05/2024.
//

#ifndef MINIRT_H
# define MINIRT_H

# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/fcntl.h>
# include <ft_maths.h>
# include <float.h>
# include <MLX42/MLX42.h>
# include <libft.h>
# include <ft_utils.h>
# include <mlx_utils.h>
# include <miniRT_hooks.h>

# ifndef WIDTH
#  define WIDTH 1920
# endif //WIDTH

# ifndef HEIGHT
#  define HEIGHT 1080
# endif //HEIGHT

typedef struct	s_rgb
{
	int r;
	int g;
	int b;
}	t_rgb;

typedef struct	s_line
{
	t_coordinates		origin;
	t_vector			direction;
}	t_line;

typedef struct	s_ambient_light
{
	float	ratio;
	t_rgb	rgb;
}	t_ambient_light;

typedef struct	s_camera
{
	t_coordinates		center;
	t_vector			vector;
	int 				fov;
}	t_camera;

typedef struct	s_light
{
	t_coordinates	center;
	float 			brightness;
}	t_light;

typedef struct	s_sphere
{
	t_coordinates	center;
	float			diameter;
	t_rgb			rgb;
}	t_sphere;

typedef struct	s_plane
{
	t_coordinates	coordinates;
	t_vector		vector;
	t_rgb			rgb;
}	t_plane;

typedef struct	s_cylinder
{
	t_coordinates	center;
	t_vector		vector;
	float			diameter;
	float			height;
	t_rgb			rgb;
}	t_cylinder;

typedef struct	s_scene
{
	t_ambient_light	*ambient_light;
	t_camera		*camera;
	t_light			*light;
	t_sphere		**sphere;
	t_plane			**plane;
	t_cylinder 		**cylinder;
}	 t_scene;

t_scene	parse_file(char *filename);
void	free_render_scene(t_scene *scene);
int				render_scene(mlx_t *mlx, t_scene *scene);
void	print_all(t_scene *scene);

#endif //MINIRT_H
