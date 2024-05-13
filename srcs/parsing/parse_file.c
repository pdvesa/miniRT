//
// Created by Jules Cayot on 13/05/2024.
//

#include <miniRT.h>

char	*readfile(char *filename) {
	char	*content;
	char	buffer;
	int		fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (NULL);

}

t_render_scene	parse_file(char *filename) {

}
