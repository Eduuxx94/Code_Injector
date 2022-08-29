#ifndef INJECT_CODE_H
# define INJECT_CODE_H

# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>
# include "get_next_line.h"
# include <string.h>

typedef struct s_data {
	int		line;
	int		bytes_read;
	int		file_out;
	int		fd;
	int		fd_value;
	char	*text_value;
	char	*current_line;
	char	*last_line;
	char	*path_file;
	char	*new_file;
	char	*date;
}			t_data;

// Main Functions
void	ft_put_text(t_data *data);
void	ft_open_file(t_data *data);
void	ft_exit(t_data *data, char *str, int error);
int		main(int argc, char **argv);

#endif