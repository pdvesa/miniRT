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
int		scene_parser(void **objs_ptr, char **content, int *n_objs, int item);

#endif //MINIRT_PARSING_H
