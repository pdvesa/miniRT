/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svesa <svesa@student.hive.fi>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 16:53:39 by svesa             #+#    #+#             */
/*   Updated: 2024/06/05 20:41:28 by svesa            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <miniRT_parsing.h>

char	*read_fd(int fd)
{
	char	*content;
	char	buffer[10];
	int		read_return;

	content = NULL;
	buffer[9] = 0;
	read_return = (int) read(fd, &buffer, 9);
	while (read_return > 0)
	{
		content = ft_strappend(content, buffer, 10);
		if (!content)
		{
			ft_putendl_fd("MiniRT : Malloc error", 2);
			return (NULL);
		}
		read_return = (int) read(fd, &buffer, 9);
	}
	if (read_return == -1)
	{
		ft_putendl_fd("MiniRT : Error reading file", 2);
		if (content)
			free(content);
		content = NULL;
	}
	return (content);
}

char	**read_file(char *filename)
{
	char	*content;
	char	**splitted_content;
	int		fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (perror("MiniRT : "), NULL);
	content = read_fd(fd);
	close(fd);
	splitted_content = ft_split(content, '\n');
	free(content);
	return (splitted_content);
}
