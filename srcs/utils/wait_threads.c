//
// Created by jules on 03/08/2024.
//

#include <ft_utils.h>

void	wait_threads(int n, pthread_t *threads)
{
	int	i;

	i = 0;
	while (i < n)
	{
		pthread_join(threads[i], NULL);
		i++;
	}
}
