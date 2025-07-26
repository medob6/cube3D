NAME        = cub3D

CC          := cc

MANDATORY_DIR := mandatory
BONUS_DIR     := bonus

LIBFT_PATH          := $(MANDATORY_DIR)/libft
LIBFT_BONUS_PATH    := $(BONUS_DIR)/libft

LIBFT         := $(LIBFT_PATH)/libft.a
LIBFT_BNS     := $(LIBFT_BONUS_PATH)/libft.a

INCLUDES       := -I$(MANDATORY_DIR)/includes -I$(MANDATORY_DIR)/libft
INCLUDES_BNS   := -I$(BONUS_DIR)/includes -I$(BONUS_DIR)/libft -g $(shell sdl2-config --cflags)

CFLAGS         := -Wall -Wextra -Werror $(INCLUDES)
CFLAGS_BNS     := -Wall -Wextra -Werror $(INCLUDES_BNS)

LDFLAGS        := -lmlx -lXext -lX11 -lm -Ofast
LDFLAGS_BNS    := $(LDFLAGS) $(shell sdl2-config --libs)

MAIN_SRC       := main.c
PARSER_SRC     := check_fc.c check_map.c errors_msg.c get_val_of_file.c parser.c tools1.c tools2.c
RAYCASTER_SRC  := cleanup.c draw_wall_slice.c geometry_utils.c helpers.c init_resorces2.c keys_api.c minimap_utils.c \
                  ray_cast.c wall_color.c draw_sections.c frame_utils.c helpers2.c horizontal_raycast.c init_resorces.c \
                  minimap.c movements.c vertical_raycast.c menu.c

SRCS           := $(addprefix $(MANDATORY_DIR)/src/, $(MAIN_SRC)) \
                  $(addprefix $(MANDATORY_DIR)/src/parser/, $(PARSER_SRC)) \
                  $(addprefix $(MANDATORY_DIR)/src/raycaster/, $(RAYCASTER_SRC))

OBJS           := $(SRCS:.c=.o)

SRCS_BNS       := $(addprefix $(BONUS_DIR)/src/, $(MAIN_SRC)) \
                  $(addprefix $(BONUS_DIR)/src/parser/, $(PARSER_SRC)) \
                  $(addprefix $(BONUS_DIR)/src/raycaster/, $(RAYCASTER_SRC))
OBJS_BNS       := $(SRCS_BNS:.c=.o)

HEADER_FILES   := $(MANDATORY_DIR)/includes/cub.h $(MANDATORY_DIR)/includes/raycaster.h

all: $(LIBFT) $(NAME)

bonus: $(OBJS_BNS) $(LIBFT_BNS)
	@$(CC) $(CFLAGS_BNS) $(OBJS_BNS) $(LIBFT_BNS) -o $(NAME) $(LDFLAGS_BNS)

$(LIBFT_BNS):
	@make -C $(LIBFT_BONUS_PATH)

$(LIBFT):
	@make -C $(LIBFT_PATH)


$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME) $(LDFLAGS)

bonus/%.o: bonus/%.c
	@$(CC) $(CFLAGS_BNS) -c $< -o $@

%.o: %.c $(HEADER_FILES)
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -rf $(OBJS) $(OBJS_BNS)
#	make -C $(LIBFT_PATH) clean
	@make -C $(LIBFT_BONUS_PATH) clean

fclean: clean
	@rm -rf $(NAME)
#	make -C $(LIBFT_PATH) fclean
	@make -C $(LIBFT_BONUS_PATH) fclean

re: fclean all

.PHONY: all clean fclean re bonus
