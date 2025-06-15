CC = cc -fsanitize=address -g
CFLAGS =  -Wall -Wextra -Werror 
LDFLAGS = -lmlx -lXext -lX11 -lm
SRC = src/main.c 
OBJ = $(SRC:.c=.o)
NAME = cub3D
RM = rm -f

all: $(NAME)

$(NAME): $(OBJ) 
	@$(CC) $(OBJ) $(LDFLAGS) -o $(NAME)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean: 
	@$(RM) $(OBJ)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re