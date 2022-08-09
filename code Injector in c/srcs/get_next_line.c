#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>

char	*get_next_line(int fd)
{
	static char	buff[BUFFER_SIZE];
	int			buff_size;
	char		*line;
	int			line_size;

	line_size = 0;
	line = NULL;
	buff_size = 0;
	while (1)
	{
		if (!buff[0])
			buff_size = read(fd, buff, BUFFER_SIZE);
		else
			buff_size = 1;
		line_size += get_size_linha(buff);
		if (buff_size > 0)
			line = ft_realoc(line, buff, line_size, &buff_size);
		if (buff_size <= 0)
			return (line);
	}
	return (line);
}
