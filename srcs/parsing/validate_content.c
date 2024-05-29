//
// Created by Jules Cayot on 5/14/24.
//

#include <miniRT_parsing.h>

int	in_categories(char *content, int *objs_num)
{
	const char	category[6][3] = {"A", "C", "L", "sp", "pl", "cy"};
	int 		i;
	int 		spaces;

	spaces = 0;
	while (ft_isspace(content[spaces]))
		spaces++;
	i = 0;
	while (i < 6)
	{
		if (ft_strncmp(content + spaces, category[i], ft_strlen(category[i])) &&
			*(content + spaces + ft_strlen(category[i])) == ' ')
		{
			objs_num[i]++;
			return (1);
		}
		i++;
	}
	ft_putendl_fd("MiniRT : invalid content in provided file", 2);
	return (0);
}
void	validate_error(int error_num)
{
	if (error_num == 1)
		ft_putendl_fd("MiniRT : more than one ambient light in provided file", 2);
	if (error_num == 2)
		ft_putendl_fd("MiniRT : no camera in provided file", 2);
	if (error_num == 3)
		ft_putendl_fd("MiniRT : more than one camera in provided file", 2);
	if (error_num == 4)
		ft_putendl_fd("MiniRT : more than one light source in provided file", 2);
}

int	valid_category(char **content, int *objs_num)
{
	int i;

	i = 0;
	while (content[i])
	{
		if (!in_categories(content[i], objs_num))
			return (0);
		i++;
	}
	if (objs_num[A] > 1)
		return (validate_error(1), 0);
	if (objs_num[C] == 0)
		return (validate_error(2), 0);
	if (objs_num[C] > 1)
		return (validate_error(3), 0);
	if (objs_num[L] > 1)
		return (validate_error(4), 0);
	return (1);
}
