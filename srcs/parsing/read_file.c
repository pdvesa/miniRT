//
// Created by Jules Cayot on 5/14/24.
//

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
		content = ft_strappend(content, buffer);
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

char	*read_file(char *filename)
{
	char	*result;
	int		fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (perror("MiniRT : "), NULL);
	result = read_fd(fd);
	close(fd);
	return (result);
}
