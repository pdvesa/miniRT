/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svesa <svesa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 11:16:09 by svesa             #+#    #+#             */
/*   Updated: 2024/05/29 13:55:50 by svesa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT_parsing.h>

// idr if we can have random data in file
// also maybe remember to check return values, it is inconsistent

char	*skip_white(char *str)
{
	while (ft_isspace(*str))
		*str++;
	return (str);
}

char	*find_content_str(char **content, char item)
{
	char	*temp;
	int		i;

	i = 0;
	while (content[i])
	{
		temp = skip_white(content[i]);
		if (item == *temp)
			return (temp);
	i++;		
	}
}

char	**find_content_array(char **content, char item, int size)
{
	char	**array;
	int 	i;

	array = malloc(sizeof(char *) * size);
	if (!array)
		return (NULL);
	i = 0;
	while (i < size)
	{
	}
	return (array); 
}

int	parse_ambient(t_ambient_light **ambient, char **content) 
{
	char	*content_str;
	
	content_str = find_content_str(content, 'A');
	content_str = skip_white(content_str);
	(*ambient)->ratio = special_floatoi(content_str); 
	if ((*ambient)->ratio < 0 || (*ambient)->ratio > 1) 
		return (EXIT_FAILURE); // make error handler for messages
	content_str = skip_white(content_str);
	(*ambient)->rbg.r = special_atoi(content_str);
	if ((*ambient)->rbg.r > 255 || (*ambient)->rbg.r < 0)
		return (EXIT_FAILURE);
	content_str = skip_white(content_str);
	(*ambient)->rbg.g =	special_atoi(content_str);
	if ((*ambient)->rbg.g > 255 || (*ambient)->rbg.g < 0)
		return (EXIT_FAILURE);
	content_str = skip_white(content_str);
	(*ambient)->rbg.b =	special_atoi(content_str);
	if ((*ambient)->rbg.b > 255 || (*ambient)->rbg.b < 0)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

// 0.5345345 might not be valid, ie. only 0.x might be, idk
// also most likely need to actually malloc here
// fix atois to move the pointer for ez lif
// do we care if there is garbage in string after this ??//??

int	parse_camera(t_camera **camera, char **content)
{
	char *content_str;

	content_str = find_content_str(content, 'C');
	content_str = skip_white(content_str);
}

int	parse_light(t_light **light, char **content) 
{
	char *content_str;
	
	content_str = find_content_str(content, 'L');
}

int	parse_sphere(t_sphere **sphere, char **content, int n_objs)
{
	char **content_array;
	
	content_array = find_content_array(content, 'sp', n_objs);
	if (!content_array && n_objs)
		return (EXIT_FAILURE);
}

int	parse_plane(t_plane **plane, char **content, int n_objs)
{
	char **content_array;
	
	content_array = find_content_array(content, 'pl', n_objs);
	if (!content_array && n_objs)
		return (EXIT_FAILURE);
}

int	parse_cylinder(t_cylinder **cylinder, char **content, int n_objs)
{
	char **content_array;
	
	content_array = find_content_array(content, 'cy', n_objs);
	if (!content_array && n_objs)
		return (EXIT_FAILURE);
}

int scene_parser(t_scene *scene, char **content, int *n_objs, int item)
{	
	if (item == A)
		return (parse_ambient(scene->ambient_light, content));
	else if (item == C)
		return (parse_camera(scene->camera, content));
	else if (item == L)
		return (parse_light(scene->light, content));
	else if (item == sp)
		return (parse_sphere(scene->sphere, content, n_objs[3]));
	else if (item == pl)
		return (parse_plane(scene->plane, content, n_objs[4]));
	else if (item == cyka)
		return (parse_cylinder(scene->cylinder, content, n_objs[5]));
	else 
		return (EXIT_FAILURE);
}
