/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trans_utils.c                                       :+:      :+:    :+:  */
/*                                                    +:+ +:+         +:+     */
/*   By: svesa <svesa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 16:52:37 by svesa             #+#    #+#             */
/*   Updated: 2024/06/07 16:07:59 by svesa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT_trans.h>
#include <get_next_line.h>

void	print_instructions(void)
{
	printf("Possible transformable parameters :\n\tdia (num) for diameter\n\t");
	printf("hgt (num) for height\n\torient (num,num,num) for change of");
	printf("direction\n\tcord (num,num,num) for relocation\n");
	printf("Examples: 'dia 35' will change selected sphere diameter to 35\n");
	printf("'orient 1,1,1' will change selected objects directional vector!\n");
	printf("Only one modification per press of button, else reset program!\n");
	printf("If situation occurs where you lost your memories and you need ");
	printf("to reprint these instructions press A (for acute amnesia)\n");
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

void	translate_error(char **array)
{
	ft_strarray_free(array);
	ft_putendl_fd("Follow the damn instructions\n", 2);
}

char	**sanitize_input(void)
{
	char	*input;
	char	**cont_arr;
	int		i;

	printf("Input please\n");
	input = get_next_line(1); //when we wait exiting is kind eh also make fails because makefile boomboom
	cont_arr = ft_split(input, ' ');
	free(input);
	if (!cont_arr)
		return (NULL); //malloc fail has no mesasge but who cares malloc never fails
	if (ft_strarray_len(cont_arr) != 2)
		return (ft_strarray_free(cont_arr), NULL);
	i = 0;
	while (cont_arr[1][i])
	{
		if (cont_arr[1][i] == '\n' || cont_arr[1][i] == '\t'
				|| cont_arr[1][i] == '\r')
			cont_arr[1][i] = '\0';
		i++;
	}
	return (cont_arr);
}

void	*get_value(void *original, void *mod_value, char *str, int mod_num)
{
	int	error;

	error = 0;
	if (mod_num == 1)
		error = extract_cords((t_coordinates *)mod_value, str);
	else if (mod_num == 2)
		error = extract_vector((t_vector *)mod_value, str);
	else if (mod_num == 3)
		*(float *)mod_value = (float) get_numbers(str, 1);
	if (error || (mod_num == 3 && (*(float *)mod_value < 0.0F
				|| *(float *)mod_value > HEIGHT)))
		return (ft_putendl_fd("Follow the damn instructions\n", 2), original);
	return (mod_value);
}
