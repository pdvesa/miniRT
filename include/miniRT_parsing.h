//
// Created by Jules Cayot on 5/14/24.
//

#ifndef MINIRT_PARSING_H
# define MINIRT_PARSING_H

# include "miniRT.h"

typedef enum s_objs_index
{
	A = 0,
	C = 1,
	L = 2,
	sp = 3,
	pl = 4,
	cyka = 5
}	t_objs_index;

typedef struct s_object_amount
{
	int n_ambient;
	int	n_camera;
	int n_light;
	int n_sphere;
	int n_plane;
	int n_cylinder;

}	t_obj_n;

char	**read_file(char *filename);
int		valid_category(char **content, int objs_num[6]);
int		scene_parser(t_scene *scene, char **content, int *n_objs, int item);
int	parse_ambient(t_scene *scene, char **content);
int	parse_camera(t_scene *scene, char **content);
int	parse_light(t_scene *scene, char **content);
char	*skip_white(char *str);
char	*find_content_str(char **content, char item);
double get_numbers(char *str, int type);
int	save_vector(t_scene *scene, char *content_str, int obj_type, int i);
int	save_cords(t_scene *scene, char *content_str, int obj_type, int i);
int	extract_rgb(t_rgb *colors, char *content);
void extract_error(int object);
int	parse_sphere(t_scene *scene, char **content, int n_objs);
int	parse_plane(t_scene *scene, char **content, int n_objs);
int	parse_cylinder(t_scene *scene, char **content, int n_objs);

#endif //MINIRT_PARSING_H
