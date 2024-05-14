//
// Created by Jules Cayot on 5/14/24.
//

#include <miniRT_parsing.h>

int	is_category(const char *content)
{
	const char	category[6][3] = {"A", "C", "L", "sp", "pl", "cy"};
	int 		i;

	i = 0;
	while (i < 6)
	{
		if (ft_strncmp(content, category[i], ft_strlen(category[i])))
			return (1);
		i++;
	}
	return (0);
}

int	valid_category(const char *content)
{
	int	i;

	i = 0;
	while (content[i])
	{
		while (ft_isspace(content[i]))
			i++;

	}
}
