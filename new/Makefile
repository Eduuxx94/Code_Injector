NAME = inject_code

SRC_PATH = ./srcs/
OBJ_PATH = ./objs/
INC_PATH = ./includes/

GET_NEXT_LINE = get_next_line.c

SRC_NAME = main.c $(GET_NEXT_LINE)
OBJ_NAME = $(SRC_NAME:.c=.o)

SRC = $(addprefix $(SRC_PATH), $(SRC_NAME))
OBJ = $(addprefix $(OBJ_PATH), $(OBJ_NAME))

CC = gcc
CFLAGS = -g -fsanitize=address -Wall -Wextra -Werror

$(OBJ_PATH)%.o:$(SRC_PATH)%.c
	@mkdir -p $(OBJ_PATH)
	$(CC) $(CFLAGS) -I $(INC_PATH) -o $@ -c $<

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $@

all: $(NAME)

clean:
	rm -rf $(OBJ_PATH)

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re