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
	{
		ft_putendl_fd("MiniRT : more than one ambient light in provided file", 2);
		return (0);
	}
	if (objs_num[C] == 0)
	{
		ft_putendl_fd("MiniRT : no camera in provided file", 2);
		return (0);
	}
	return (1);
}
