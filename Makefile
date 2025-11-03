NAME        = cub3D

CC          =  cc

MANDATORY_DIR =  mandatory
BONUS_DIR     =  bonus

LIBFT_PATH          =  $(MANDATORY_DIR)/libft
LIBFT_BONUS_PATH    =  $(BONUS_DIR)/libft

LIBFT         =  $(LIBFT_PATH)/libft.a
LIBFT_BNS     =  $(LIBFT_BONUS_PATH)/libft.a

INCLUDES       =  -I$(MANDATORY_DIR)/includes -I$(MANDATORY_DIR)/libft
INCLUDES_BNS   =  -I$(BONUS_DIR)/includes -I$(BONUS_DIR)/libft  -I/usr/include/SDL2 -D_REENTRANT -I$(HOME)/goinfre/ffmpeg_build/include 

CFLAGS         =  -Wall -Wextra -Werror  $(INCLUDES) 

SDL2_CFLAGS =  -I/usr/include/SDL2 -D_REENTRANT
 
CFLAGS_BNS =  $(SDL2_CFLAGS) $(INCLUDES_BNS)

LDFLAGS        =  -lmlx -lXext -lX11 -lm  -g3 -Ofast #-fsanitize=address 


SDL2_LIBS =  -lSDL2
LDFLAGS_BNS    = -L$(HOME)/goinfre/ffmpeg_build/lib \
	-Wl,--start-group \
	-lavformat -lavcodec -lswscale -lavutil -lswresample \
	-Wl,--end-group \
	$(SDL2_LIBS) \
	-lz -lpthread -ldl -lm -llzma \
	-lmlx -lX11 -lXext -g3  -Ofast #-fsanitize=address 

MAIN_SRC       =  main.c
MAIN_SRC_BNS      =  main.c  main_tools1.c  main_tools2.c  main_tools3.c  main_tools4.c  main_tools.c
PARSER_SRC_BNS     =  check_fc.c tools_flood_fill.c check_map.c errors_msg.c get_val_of_file.c parser.c tools1.c tools2.c flood_fill.c
PARSER_SRC     =  check_fc.c check_map.c errors_msg.c get_val_of_file.c parser.c tools1.c tools2.c
RAYCASTER_SRC  =  cleanup.c draw_wall_slice.c geometry_utils.c helpers.c helper_funcs.c keys_api.c minimap_utils.c \
                  ray_cast.c wall_color.c draw_sections.c frame_utils.c helpers2.c horizontal_raycast.c init_resorces.c \
                  minimap.c movements.c vertical_raycast.c  
RAYCASTER_SRC_BNS = $(RAYCASTER_SRC) move_toward_door.c minimap_utils2.c init_graphic_resorces.c raycaster_init.c raycaster_door_utils.c \
					raycaster_process.c vdoor_intersection.c section_init.c wall_color_tools.c
VIDEO_PLAYER =   video_audio.c    video_codec_tools1.c  video_tools3.c  video_utils.c \
					video.c          video_codec_tools.c   video_tools.c \
					video_cleanup.c  video_tools1.c        video_utils1.c \
					video_codec.c    video.tools2.c        video_utils2.c
MENU_SRC	   =  exit.c start.c control.c menu.c no.c yes.c return.c mlx_event.c
COUNTER_TIME_SRC	   =   time_of_player.c design.c  init_res.c  tools.c
MOUSE_SRC	   =   mouse_hook.c init_game.c

HEADER_SRC = cub.h  parser.h  raycaster.h

HEADER_SRC_BNS = array.h  cub_bs.h  pars_b.h  raycaster_bs.h  video_bs.h

SRCS           =  $(addprefix $(MANDATORY_DIR)/src/, $(MAIN_SRC)) \
                  $(addprefix $(MANDATORY_DIR)/src/parser/, $(PARSER_SRC)) \
                  $(addprefix $(MANDATORY_DIR)/src/raycaster/, $(RAYCASTER_SRC))

OBJS           =  $(SRCS:.c=.o)

SRCS_BNS       =  $(addprefix $(BONUS_DIR)/src/main/, $(MAIN_SRC_BNS)) \
                  $(addprefix $(BONUS_DIR)/src/parser/, $(PARSER_SRC_BNS)) \
                  $(addprefix $(BONUS_DIR)/src/raycaster/, $(RAYCASTER_SRC_BNS)) \
				  $(addprefix $(BONUS_DIR)/src/menu/, $(MENU_SRC)) \
                  $(addprefix $(BONUS_DIR)/src/counter_time/, $(COUNTER_TIME_SRC)) \
                  $(addprefix $(BONUS_DIR)/src/mouse/, $(MOUSE_SRC)) \
				  $(addprefix $(BONUS_DIR)/src/vid_player/, $(VIDEO_PLAYER))
				

OBJS_BNS       =  $(SRCS_BNS:.c=.o)
HEADER_FILES   =  $(addprefix $(MANDATORY_DIR)/includes/, $(HEADER_SRC))
HEADER_FILES_BNS =  $(addprefix $(BONUS_DIR)/includes/, $(HEADER_SRC_BNS))

all: $(LIBFT) $(NAME)

bonus: $(OBJS_BNS) $(LIBFT_BNS)
	@$(CC) $(CFLAGS_BNS) $(OBJS_BNS) $(LIBFT_BNS) -o $(NAME) $(LDFLAGS_BNS)

$(LIBFT_BNS):
	@make -C $(LIBFT_BONUS_PATH)

$(LIBFT):
	@make -C $(LIBFT_PATH)


$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME) $(LDFLAGS) 

bonus/%.o: bonus/%.c $(HEADER_FILES_BNS)
	@$(CC) $(CFLAGS_BNS) -c $< -o $@

%.o: %.c $(HEADER_FILES)
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -rf $(OBJS) $(OBJS_BNS)
	@make -C $(LIBFT_BONUS_PATH) clean
	@make -C $(LIBFT_PATH) clean

fclean: clean
	@rm -rf $(NAME)
	@make -C $(LIBFT_BONUS_PATH) fclean
	@make -C $(LIBFT_PATH) fclean

re: fclean all

.PHONY: all clean fclean re bonus
