NAME = cub3D

CC = cc

LDFLAGS = -lmlx -lXext -lX11 -lm -Ofast

CFLAGS = -g3 -Wall -Wextra -Werror -Imandatory/includes -Imandatory/libft #-fsanitize=address 

MAIN_SRC = main.c

PARSER_SRC = check_fc.c  check_map.c  errors_msg.c  get_val_of_file.c  parser.c  tools1.c  tools2.c

RAY_CASTER = cleanup.c draw_wall_slice.c  geometry_utils.c  helpers.c  init_resorces2.c  keys_api.c  minimap_utils.c  ray_cast.c \
			wall_color.c draw_sections.c  frame_utils.c  helpers2.c  horizontal_raycast.c  init_resorces.c   minimap.c \
			movements.c  vertical_raycast.c


SRCS = $(addprefix mandatory/src/, $(MAIN_SRC)) $(addprefix mandatory/src/parser/, $(PARSER_SRC)) $(addprefix mandatory/src/raycaster/, $(RAY_CASTER)) 

OBJS = $(SRCS:.c=.o)

HEADER_FILES = mandatory/includes/cub.h mandatory/includes/raycaster.h

LIBFT_PATH = mandatory/libft
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