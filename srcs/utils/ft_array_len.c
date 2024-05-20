//
// Created by Jules Cayot on 5/20/24.
//

#include <ft_utils.h>

size_t	ft_array_len(void **array)
{
	size_t	len;

	len = 0;
	while (array[len])
		len++;
	return (len);
}
