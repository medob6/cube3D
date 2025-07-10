NAME = cub3D

CC = cc

LDFLAGS = -lmlx -lXext -lX11 -lm -Ofast

CFLAGS = -g3 -Wall -Wextra -Werror -Iincludes -Ilibft #-fsanitize=address 

MAIN_SRC = main.c

PARSER_SRC = check_fc.c  check_map.c  errors_msg.c  get_val_of_file.c  parser.c  tools1.c  tools2.c

RAY_CASTER = ray_cast.c init_resorces.c keys_api.c movements.c cleanup.c helpers.c minimap.c


SRCS = $(addprefix src/, $(MAIN_SRC)) $(addprefix src/parser/, $(PARSER_SRC)) $(addprefix src/raycaster/, $(RAY_CASTER)) 

OBJS = $(SRCS:.c=.o)

HEADER_FILES = includes/cub.h includes/raycaster.h

LIBFT_PATH = libft
LIBFT = $(LIBFT_PATH)/libft.a

all: $(LIBFT) $(NAME)

$(LIBFT):
	@make -C $(LIBFT_PATH)
	@make bonus -C $(LIBFT_PATH)

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS)  $(OBJS) $(LIBFT) -o $(NAME) $(LDFLAGS)

%.o: %.c $(HEADER_FILES)
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -rf $(OBJS)
	@make -C $(LIBFT_PATH) clean

fclean: clean
	@rm -rf $(NAME)
	@make -C $(LIBFT_PATH) fclean

re: fclean all

.PHONY: all clean fclean re