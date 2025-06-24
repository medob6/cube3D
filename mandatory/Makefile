NAME = cub

CC = cc

LDFLAGS = #-lmlx -lXext -lX11 -lm

CFLAGS = -g3 -Wall -Wextra -Werror -Iincludes -Ilibft

MAIN_SRC = main.c

PARSER_SRC = check_fc.c  check_map.c  parser.c  sum_checks.c  utils.c

SRCS = $(addprefix src/, $(MAIN_SRC)) $(addprefix src/parser/, $(PARSER_SRC))

OBJS = $(SRCS:.c=.o)

HEADER_FILES = includes/cub.h

LIBFT_PATH = libft
LIBFT = $(LIBFT_PATH)/libft.a

all: $(LIBFT) $(NAME)

$(LIBFT):
	@make -C $(LIBFT_PATH)
	@make bonus -C $(LIBFT_PATH)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(LDFLAGS) $(OBJS) $(LIBFT) -o $(NAME)

%.o: %.c $(HEADER_FILES)
	@$(CC) $(CFLAGS) $(LDFLAGS) -c $< -o $@

clean:
	@rm -rf $(OBJS)
	@make -C $(LIBFT_PATH) clean

fclean: clean
	@rm -rf $(NAME)
	@make -C $(LIBFT_PATH) fclean

re: fclean all

.PHONY: all clean fclean re