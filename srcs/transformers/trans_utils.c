/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trans_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svesa <svesa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 16:52:37 by svesa             #+#    #+#             */
/*   Updated: 2024/06/07 16:07:59 by svesa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT_trans.h>
# include <get_next_line.h>

void	print_instructions(void)
{
	printf("In order to select object to transform click it on the screen\n"); //change
	printf("Possible transformable parameters :\n\tdia (num) for diameter\n\thgt (num) for height\n\torient (num,num,num) for change of direction\n\tcord (num,num,num) for relocation\n");
	printf("Examples: 'dia 35' will change selected sphere diameter to 35, 'orient 1,1,1' will change selected object or element directional vector!\n");
	printf("Only one modification per press of button!@!\n");
	printf("If situation occurs where you lost your memories and you need to reprint these instructions press A (for acute amnesia)\n");
}

void	ft_re_render(t_hook_container *data)
{
	ray_trace(data->image, data->scene);
	if (mlx_image_to_window(data->mlx, data->image, 0, 0) == -1) // dont know if we can just re_render without deleting or do we need to make new image for not leaking
	{
		mlx_delete_image(data->mlx, data->image);
		ft_putmlx_error();
	}
}

char	**sanitize_input(void)
{
	char	*input;
	char	**cont_arr;
	int		i;

	printf("Input please\n");
	input = get_next_line(1);
	cont_arr = ft_split(input, ' ');
	free(input);
	if (!cont_arr)
		return (NULL); //malloc fail has no mesasge but who cares malloc never fails
	if (ft_strarray_len(cont_arr) != 2)
		return (ft_strarray_free(cont_arr), NULL);
	i = 0;
	while(cont_arr[1][i])
	{
		if (cont_arr[1][i] == '\n' || cont_arr[1][i] == '\t' || cont_arr[1][i] == '\r')
			cont_arr[1][i] = '\0';
		i++;
	}
	return (cont_arr);
}
