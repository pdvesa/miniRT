/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_parser2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svesa <svesa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 21:33:52 by svesa             #+#    #+#             */
/*   Updated: 2024/06/07 16:15:50 by svesa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT_parsing.h>

int	erreur_dictateur(char **array, int obj_type)
{
	ft_strarray_free(array);
	extract_error(obj_type);
	return (EXIT_FAILURE);
}

// i love norminette

int	parse_cylinder(t_scene *scene, char **content, int n_objs)
{
	int	i;

	scene->cylinder = ft_calloc(n_objs + 1, sizeof(t_cylinder *));
	if (!(scene->cylinder))
		return (EXIT_FAILURE);
	i = 0;
	while (i < n_objs)
	{
		scene->cylinder[i] = ft_calloc(1, sizeof(t_cylinder));
		if (!(scene->cylinder[i]))
			return (EXIT_FAILURE);
		if (extract_cylinder(scene, content, i))
			return (EXIT_FAILURE);
		i++;
	}
	scene->cylinder[i] = NULL;
	return (EXIT_SUCCESS);
}
