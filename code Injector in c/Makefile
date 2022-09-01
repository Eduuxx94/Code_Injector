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
#Disable $CFLAGS if any error ocurred while compile or execution...
CFLAGS = -O3 #-O3: the highest level of optimization possible. It enables optimizations that are expensive in terms of compile time and memory usage. Compiling with -O3 is not a guaranteed way to improve performance, and in fact, in many cases, can slow down a system due to larger binaries and increased memory usage. -O3 is also known to break several packages. Using -O3 is not recommended. However, it also enables -ftree-vectorize so that loops in the code get vectorized and will use AVX YMM registers.

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