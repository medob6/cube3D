/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_bs.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbousset <mbousset@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 15:39:51 by mbousset          #+#    #+#             */
/*   Updated: 2025/07/31 09:52:40 by mbousset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_BS_H
# define CUB_BS_H
# include "get_next_line.h"
# include "libft.h"
# include "parser_bs.h"
# include <SDL2/SDL.h>
# include <errno.h>
# include <fcntl.h>
# include <math.h>
# include <mlx.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

# define WALL_HIGHT 64

# define WALL_WIDTH 126

// keys
# define KEY_ESCAPE 65307
# define KEY_UP 119
# define KEY_DOWN 115
# define KEY_LEFT 97
# define KEY_RIGHT 100
# define ARROW_UP 65362
# define ARROW_DOWN 65364
# define ARROW_LEFT 65361
# define ARROW_RIGHT 65363
# define KEY_SPACE 32
# define KEY_O 111

// speed
# define MOVE_SPEED 2.5
# define ROTATE_SPEED 0.01
# define JUMP_SPEED 10
# define M_PI_3 1.0471975511965976
# define FOV_ANGLE M_PI_3

# define FRAME_DURATION_MS 40

// minimp
# define MINIMAP_SCREEN_SCALE 0.09
# define ICON_SCALE 0.14
# define PLAYER_SCALE 0.20

//menu
# define NB_BUTTON 6
# define NB_IMG_MENU 18

typedef enum e_graphic
{
	E_WALL,
	N_WALL,
	W_WALL,
	S_WALL,
	N_ICONE,
	ARROW,
	DOOR,
	PORTAL,
}				t_graphic;

typedef enum e_graphic_menu
{
	BG_IMG,
	START_IMG,
	CONTROL_IMG,
	EXIT_IMG,
	H_START_IMG,
	H_CONTROL_IMG,
	H_EXIT_IMG,
	CONTROL_PAGE_IMG,
	EXIT_PAGE_IMG,
	NO_IMG,
	YES_IMG,
	H_NO_IMG,
	H_YES_IMG,
	RETURN_IMG,
	H_RETURN_IMG,
	NUMBERS_IMG,
	POINT_IMG,
	TIMER_BG_IMG
}				t_graphic_menu;

typedef enum e_timer_num
{
	FP_MIN,
	SP_MIN,
	POINT,
	FP_SEC,
	SP_SEC,
	TIMER_BG
}				t_timer_num;

typedef enum e_button_name
{
	START,
	CONTROL,
	EXIT,
	NO,
	YES,
	RETURN
}				t_button_name;

typedef struct s_point
{
	double		x;
	double		y;
	double		z;
}				t_point;

typedef struct s_door
{
	t_point		pos;
	bool		opening;
	bool		closing;
	bool		animating;
	bool		in_range;
	int			frame;
	long long	last_update;
}				t_door;

typedef struct s_pair
{
	double		x;
	double		y;
}				t_pair;

typedef struct s_image
{
	void		*img;
	char		*addr;
	int			w;
	int			h;
	int			bpp;
	int			line_len;
	int			endian;
	int			frames;
}				t_image;

typedef struct s_player
{
	t_image		sprite;
	t_point		p;
	double		angle;
	double		hieght;
	bool		moving;
	bool		jumping;
	bool		can_open_door;
	int			door_x;
	int			door_y;
}				t_player;

typedef struct s_map
{
	char		**arr;
	int			map_w;
	int			map_h;
}				t_map;

typedef struct s_keys
{
	int			code;
	bool		press;
}				t_key;

typedef struct s_data
{
	t_map		map;
	char		*paths[4];
	int			ceiling_clr;
	int			floor_clr;
	t_door		*door;
	int			nb_door;
}				t_data;

typedef struct s_circle
{
	t_point		c;
	double		radius;

}				t_circle;

typedef struct s_mm_scale
{
	double		world_zoom;
	double		px_border;
}				t_mm_scale;

typedef struct s_game t_game;

typedef struct s_button
{
    t_image *img;
	int name;
    int start_x;
    int start_y;
    int end_x;
    int end_y;
    int width;
    int height;
	void (*on_click)(t_game* game,int button);
	void (*on_hover)(t_game* game,int button);
} t_button;

typedef struct s_timer
{
    t_image *img;
	int name;
    int start_x;
    int start_y;
    int end_x;
    int end_y;
    int width;
    int height;
	int sec;
	int min;
} t_timer;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	int			win_h;
	int			win_w;
	int			end_start_menu;
	int			nb_of_doors;
	t_data		data;
	t_player	player;
	t_key		keys[11];
	t_image		graphics[8];
	t_image		graphic_menu[NB_IMG_MENU];
	t_button	buttons[NB_BUTTON];
	t_timer		timer[6];
	t_door		*doors;
	t_image		display;
	t_door		exit;
	bool		passed;
	int portal_frame;
}				t_game;

/////////////////////////////
void create_yes_button(t_game *game,t_button *button);
void create_return_button(t_game *game,t_button *button);
void create_no_button(t_game *game,t_button *button);
void create_exit_button(t_game *game,t_button *button);
void create_start_button(t_game *game,t_button *button);
void create_control_button(t_game *game,t_button *button);
int check_button(t_game *game, int x ,int y);
int	game_loop(t_game *game);
void draw_menu(t_game *game);
void put_bg(t_game *game, t_image *img);
void put_imag(t_game *game, t_button *img_info);
void init_img_menu(t_game *game);
void draw_timer(t_game *game);
void init_timer_pic(t_game *game);
void	put_pixel(t_game *game, int x, int y, int color);
void put_time_imag(t_game *game, t_timer *img_info , int index);
long int get_time_sec();

/////////////////////////////

t_door			get_door(int x, int y);
int				handle_close(void);
void			cleanup(int code);
void			update_player(t_game *game);
t_game			*get_game(void);
bool			is_valid_dir(char dir);
void			init_image_fram(t_game *game, t_image *frame);
void			init_player(t_game *game);
void			initilize_game_resorces(t_game *game);
void			init_keys(t_game *game);
int				key_press(int keycode, t_game *game);
int				key_release(int keycode, t_game *game);
t_key			*get_key(int keycode, t_game *game);
void			print_err(char *msg);
double			normalize_angle(double angle);
void			draw_mini_map(t_game *game);
double			deg_to_rad(double a);
void			my_mlx_pixel_put(t_image fram, int x, int y, int color);
unsigned int	get_color(t_image img, int x, int y);
int				get_t(int trgb);
void			get_window_dimensions(void);
double			pow_2(double n);
double			get_old_angel(t_game *g);
int				get_icone_color(t_graphic icone, double raidus, double x,
					double y);
int				get_minimap_color(t_point p, double m_radius, t_mm_scale sc);
t_mm_scale		get_minimap_scale(t_game *g, double radius);
int				get_minimap_pixel_color(t_game *g, double rx, double ry,
					t_mm_scale sc);
void			get_icone_info(t_circle *icn, t_circle minimap,
					double icon_angle, double player_angle);

void			handle_exit(t_game *game);

// debugin
// void			draw_vert_line(t_image *img, int y, int len);


/* FUNCTIONS */
int	mouse_move(int x, int y, t_game *game);
int mouse_click(int code, int x,int y ,t_game *game);

#endif
