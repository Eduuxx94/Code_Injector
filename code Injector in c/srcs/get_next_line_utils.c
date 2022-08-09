#include "get_next_line.h"

void	ft_realoc2(char *line, char *buff, int i_line, int *buff_size)
{
	int	i_buff;
	int	i_sobra;

	i_sobra = -1;
	i_buff = 0;
	while (line && buff[i_buff])
	{
		if (i_sobra == -1)
		{
			line[i_line++] = buff[i_buff];
			if (buff[i_buff] == '\n')
				i_sobra++;
		}
		else
			buff[i_sobra++] = buff[i_buff];
		buff[i_buff++] = 0;
	}
	if (i_sobra != -1)
		*buff_size = 0;
}

void	*ft_realoc(char *line, char *buff, int line_size, int *buff_size)
{
	char	*temp;
	int		i_line;

	i_line = 0;
	temp = line;
	line = malloc(sizeof(char) * line_size + 1);
	if (line == 0)
		return (0);
	line[line_size] = 0;
	while (temp && temp[i_line])
	{
		line[i_line] = temp[i_line];
		i_line++;
	}
	if (temp)
		free(temp);
	ft_realoc2(line, buff, i_line, buff_size);
	return (line);
}

int	get_size(char *buff)
{
	if (!*buff)
		return (0);
	return (1 + get_size(buff + 1));
}

int	get_size_linha(char *buff)
{
	int	i;

	i = 0;
	while (buff[i])
	{			
		if (buff[i] == '\n')
		{
			return (i + 1);
		}
		i++;
	}
	return (i);
}
