//
// Created by Jules Cayot on 17/05/2024.
//

#include <ft_utils.h>

void	*ft_free_array(void **array)
{
	int	i;

	i = 0;
	while (array[i])
		free(array[i++]);
	free(array);
	return (NULL);
}
