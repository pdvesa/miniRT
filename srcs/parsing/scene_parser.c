/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svesa <svesa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 11:16:09 by svesa             #+#    #+#             */
/*   Updated: 2024/06/05 20:45:36 by svesa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT_parsing.h>

// idk if we can have random data in file
// also maybe remember to check return values, it is inconsistent
// 0.5345345 might not be valid, ie. only 0.x might be, idk
// do we care if there is garbage in string after this ??//??

int scene_parser(t_scene *scene, char **content, int *n_objs, int item)
{	
	if (item == A)
		return (parse_ambient(scene, content));
	else if (item == C)
		return (parse_camera(scene, content));
	else if (item == L)
		return (parse_light(scene, content));
	// else if (item == sp)
	// 	return (parse_sphere(scene, content, n_objs[3]));
	// else if (item == pl)
	// 	return (parse_plane(scene, content, n_objs[4]));
	// else if (item == cyka)
	// 	return (parse_cylinder(scene, content, n_objs[5]));
	else 
		return (EXIT_FAILURE);
}
// seems to be currently useless, fix it monke
