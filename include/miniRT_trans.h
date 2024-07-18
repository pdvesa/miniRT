/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT_trans.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svesa <svesa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 15:59:26 by svesa             #+#    #+#             */
/*   Updated: 2024/06/07 15:59:31 by svesa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_TRANS_H
# define MINIRT_TRANS_H

# include <miniRT.h>
# include <miniRT_render.h>
# include <miniRT_parsing.h>

typedef struct s_hook_data
{
	mlx_t		*mlx;
	t_scene		*scene;
	mlx_image_t	*image;
} t_hook_container;

void	print_instructions(void);
void	modify_statics(t_scene *scene, int key);
void	ft_re_render(t_hook_container *data);
void	modify_objects(t_hook_container *data);
char	**sanitize_input(void);

#endif //MINIRT_TRANS_H