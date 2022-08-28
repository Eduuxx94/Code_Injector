#include "inject_code.h"

int g_index = 0;

void	ft_put_text(t_data *data)
{
	char	*p;

	if (data->text_value && data->date)
		p = strstr(data->text_value, "<TaxPointDate>"); //Will search in code to inject where is TaxPointDate to update the variable date
	if (p  && data->date) //this will update the variable date
	{	
		p[14] = data->date[0];
		p[15] = data->date[1];
		p[16] = data->date[2];
		p[17] = data->date[3];
		p[18] = data->date[4];
		p[19] = data->date[5];
		p[20] = data->date[6];
		p[21] = data->date[7];
		p[22] = data->date[8];
		p[23] = data->date[9];
	}
	if (data->current_line)
	{
		g_index++;
		write(data->file_out, data->text_value, 530); //this will put injected code with update date in  front of "<TaxPointDate>"
		printf("%i: Injetou código\n", g_index);
	}
}

void	ft_write_file(t_data *data)
{
	while (1)
	{

		if (data->current_line)
		{
			if (data->last_line)
				free (data->last_line);
			data->last_line = data->current_line;
		}
		data->current_line = get_next_line(data->fd);
		if (data->current_line && !strncmp(data->current_line,
					"  <WorkDate>", 12)) //this will search in main code if line cointains the updated date
		{
			data->date[0] = data->current_line[12];
			data->date[1] = data->current_line[13];
			data->date[2] = data->current_line[14];
			data->date[3] = data->current_line[15];
			data->date[4] = data->current_line[16];
			data->date[5] = data->current_line[17];
			data->date[6] = data->current_line[18];
			data->date[7] = data->current_line[19];
			data->date[8] = data->current_line[20];
			data->date[9] = data->current_line[21];
		}
		if (data->current_line && !strcmp(data->current_line,
				"  <DocumentTotals>\n"))
			if (data->last_line && !strcmp(data->last_line,
					"  <CustomerID>999999</CustomerID>\n"))
				ft_put_text(data);
		if (data->current_line)
		{
			data->bytes_read = strlen(data->current_line);
			write(data->file_out, data->current_line, (data->bytes_read));
		}
		else
			break ;
	}
}

void	ft_open_file(t_data *data)
{
	data->fd = open(data->path_file, O_RDONLY); //abriu o arquivo mãe
	if (data->fd < 0)
		ft_exit(data, "A Error occurred while try open path_file\n", 0);

	data->file_out = open(data->new_file, O_RDWR | O_CREAT, 0644); //Criou o arquivo de saída
	if (data->file_out < 0)
		ft_exit(data, "A Error occurred while creating the file_out\n", 3);

	data->fd_value = open("value.txt", O_RDONLY); // abriu o arquivo incremento de texto
	if (data->fd_value < 0)
		ft_exit(data, "value.txt not find...\n", 2);

	data->text_value = malloc(sizeof(char) * 530 + 1);
	data->bytes_read = read(data->fd_value, data->text_value, 530);
	data->text_value[530] = '\0';
	data->current_line = NULL;
	data->last_line = NULL;
	data->date = malloc(sizeof(char) * 10 + 1);
	data->date[10] = '\0';
	ft_write_file(data);
}

void	ft_exit(t_data *data, char *str, int error)
{
	if (str)
		printf("%s", str);
	if (error > 0)
		printf("Error code: %i\n", error);
	else if (error == -1)
	{
		printf("%s\n", data->new_file);
	}
	exit(0);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc < 2 || argc > 3)
		ft_exit(&data, "Please use: \n./inject_code	path_file	new_path\n", 0);
	data.path_file = argv[1];
	data.new_file = "out.txt";
	if (argc == 3)
		data.new_file = argv[2];
	ft_open_file(&data);
	printf("Códico injetado %i vezes...\n", g_index);
	ft_exit(&data, "Saved file: ", -1);
	return (0);
}
