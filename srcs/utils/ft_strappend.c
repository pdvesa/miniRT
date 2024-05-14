//
// Created by Jules Cayot on 5/14/24.
//

#include <ft_utils.h>

char	*ft_strappend(char *s1, char *s2)
{
	char	*result;

	result = ft_strjoin(s1, s2);
	if (s1)
		free(s1);
	return (result);
}
