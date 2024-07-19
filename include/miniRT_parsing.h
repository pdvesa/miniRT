/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT_parsing.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svesa <svesa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 15:59:26 by svesa             #+#    #+#             */
/*   Updated: 2024/06/07 15:59:31 by svesa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_PARSING_H
# define MINIRT_PARSING_H

# ifndef ARBITARY_LIMIT
#  define ARBITARY_LIMIT 42000
# endif //ARBITARY_LIMIT

# include <miniRT.h>

typedef struct s_object_amount
{
	int	n_ambient;
	int	n_camera;
	int	n_light;
	int	n_sphere;
	int	n_plane;
	int	n_cylinder;

}	t_obj_n;

//file reading
char	**read_file(char *filename);
int		valid_category(char **content, int objs_num[6]);

//general parsers
int		parse_ambient(t_scene *scene, char **content);
int		parse_camera(t_scene *scene, char **content);
int		parse_light(t_scene *scene, char **content);
int		parse_sphere(t_scene *scene, char **content, int n_objs);
int		parse_plane(t_scene *scene, char **content, int n_objs);
int		parse_cylinder(t_scene *scene, char **content, int n_objs);

//extracting values or elements
double	get_numbers(char *str, int type);
int		save_cords(t_scene *scene, char *content_str, int obj_type, int i);
int		extract_sphere(t_scene *scene, char **content, int i);
int		extract_plane(t_scene *scene, char **content, int i);
int		extract_cylinder(t_scene *scene, char **content, int i);
int		extract_vector(t_vector *vector, char *content);
int		extract_cords(t_coordinates *cords, char *content);
int		extract_rgb(t_rgb *colors, char *content);

//utils
void	convert_tabs(char *str);
int		erreur_dictateur(char **array, int obj_type);
char	*find_content_str(char **content, char *item);
void	extract_error(int object);

#endif //MINIRT_PARSING_H
