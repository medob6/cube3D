/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_bs.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omben-ch <omben-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 08:44:11 by mbousset          #+#    #+#             */
/*   Updated: 2025/09/18 16:51:03 by omben-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_BS_H
# define CUB_BS_H
# include "get_next_line.h"
# include "libft.h"
# include "pars_b.h"
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

# define WALL_WIDTH 128

// keys
# define KEY_ESCAPE 65307
# define KEY_UP 119
# define KEY_DOWN 115
# define KEY_LEFT 97
# define KEY_RIGHT 1000
# define ARROW_UP 65362
# define ARROW_DOWN 65364
# define ARROW_LEFT 65361
# define ARROW_RIGHT 65363
# define KEY_O 111

// speed
# define MOVE_SPEED 4.0
# define ROTATE_SPEED 0.03
# define JUMP_SPEED 10
# define M_PI_3 1.0471975511965976
# define FOV_ANGLE M_PI_3
# define MOVE_MOUSE_SPEED_LEFT_RIGHT 0.0075
# define MOVE_MOUSE_SPEED_UP_DOWN 1

# define FRAME_DURATION_MS 40
# define PORTAL_FRAME_DURATION_MS 20

// minimp
# define MINIMAP_SCREEN_SCALE 0.09
# define ICON_SCALE 0.14
# define PLAYER_SCALE 0.20
# define WORLD_VISIBILITY_UNIT_FACTOR 1

// menu
# define NB_BUTTON 6
# define NB_IMG_MENU 18
# define NB_TIMER 6
# define NB_GRAGHICS 10

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
	FLOOR,
	SKY,
}						t_graphic;

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
}						t_graphic_menu;

typedef enum e_timer_num
{
	FP_MIN,
	SP_MIN,
	POINT,
	FP_SEC,
	SP_SEC,
	TIMER_BG
}						t_timer_num;

typedef enum e_button_name
{
	START,
	CONTROL,
	EXIT,
	NO,
	YES,
	RETURN,
	IN_GAME,
	IN_PLY_W_VID,
	IN_PLY_L_VID,
	IN_PLY_I_VID
}						t_button_name;

typedef struct s_point
{
	double				x;
	double				y;
	double				z;
}						t_point;

typedef struct s_door
{
	t_point				pos;
	bool				opening;
	bool				closing;
	bool				animating;
	bool				in_range;
	int					frame;
	long long			last_update;
}						t_door;

typedef struct s_pair
{
	double				x;
	double				y;
}						t_pair;

typedef struct s_image
{
	void				*img;
	char				*addr;
	int					w;
	int					h;
	int					bpp;
	int					line_len;
	int					endian;
	int					frames;
}						t_image;

typedef struct s_player
{
	t_image				sprite;
	t_point				p;
	double				angle;
	double				hieght;
	bool				moving;
	bool				jumping;
	bool				can_open_door;
	int					door_x;
	int					door_y;
}						t_player;

typedef struct s_map
{
	char				**arr;
	int					map_w;
	int					map_h;
}						t_map;

typedef struct s_keys
{
	int					code;
	bool				press;
}						t_key;

typedef struct s_data
{
	t_map				map;
	char				*paths[4];
	int					ceiling_clr;
	int					floor_clr;
	t_door				*door;
	int					nb_door;
}						t_data;

typedef struct s_circle
{
	t_point				c;
	double				radius;

}						t_circle;

typedef struct s_mm_scale
{
	double				world_zoom;
	double				px_border;
}						t_mm_scale;

typedef struct s_game	t_game;

typedef struct s_button
{
	t_image				*img;
	int					lock;
	int					name;
	int					start_x;
	int					start_y;
	int					end_x;
	int					end_y;
	int					width;
	int					height;
	void				(*on_click)(t_game *game, int button);
	void				(*on_hover)(t_game *game, int button);
}						t_button;

typedef struct s_timer
{
	t_image				*img;
	int					name;
	int					start_x;
	int					start_y;
	int					end_x;
	int					end_y;
	int					width;
	int					height;
	int					sec;
	int					min;
}						t_timer;

typedef struct s_var
{
	unsigned int		color;
	double				scale_x;
	double				scale_y;
	double				start_x;
	int					img_y;
	int					img_x;
	int					y;
	int					end;
	int					x;
}						t_var;

typedef struct s_video
{
	bool				active;
	bool				played;
	int					result;
}						t_video;

typedef enum e_vid
{
	INTRO,
	WIN,
	LOSE,
}						t_vid;
typedef struct s_game
{
	void				*mlx;
	void				*win;
	int					win_h;
	int					win_w;
	int					win_timer_h;
	int					win_timer_w;
	int					end_start_menu;
	int					nb_of_doors;
	t_data				data;
	t_player			player;
	t_player			player_info;
	t_key				keys[11];
	t_image				graphics[NB_GRAGHICS];
	t_image				graphic_menu[NB_IMG_MENU];
	t_image				img_timer;
	t_button			buttons[NB_BUTTON];
	t_timer				timer[NB_TIMER];
	t_video				videos[3];
	t_door				*doors;
	t_image				display;
	t_door				exit;
	bool				passed;
	int					portal_frame;
	int					toeg;
	long int			tmp_time;
	int					win_lose;
}						t_game;

void					create_yes_button(t_game *game, t_button *button);
void					create_return_button(t_game *game, t_button *button);
void					create_no_button(t_game *game, t_button *button);
void					create_exit_button(t_game *game, t_button *button);
void					create_start_button(t_game *game, t_button *button);
void					create_control_button(t_game *game, t_button *button);
int						check_button(t_game *game, int x, int y);
int						game_loop(t_game *game);
void					draw_menu(t_game *game);
void					put_bg(t_game *game, t_image *img);
void					put_imag(t_game *game, t_button *img_info);
void					init_img_menu(t_game *game);
void					init_timer_pic(t_game *game);
void					put_pixel(t_game *game, int x, int y, int color);
void					put_time_imag(t_game *game, t_timer *img_info,
							int index);
long int				get_time_sec(void);

t_door					get_door(int x, int y);
int						handle_close(void);
void					cleanup(int code);
void					update_player(t_game *game);
t_game					*get_game(void);
bool					is_valid_dir(char dir);
void					init_image_fram(t_game *game, t_image *frame);
void					init_player(t_game *game);
void					initilize_game_resorces(t_game *game);
void					init_keys(t_game *game);
int						key_press(int keycode, t_game *game);
int						key_release(int keycode, t_game *game);
t_key					*get_key(int keycode, t_game *game);
void					print_err(char *msg);
double					normalize_angle(double anMENU_SRC);
void					draw_mini_map(t_game *game);
double					deg_to_rad(double a);
void					my_mlx_pixel_put(t_image fram, int x, int y, int color);
unsigned int			get_color(t_image img, int x, int y);
int						get_t(int trgb);
void					get_window_dimensions(void);
double					pow_2(double n);
double					get_old_angel(t_game *g);
int						get_icone_color(t_graphic icone, double raidus,
							double x, double y);
int						get_minimap_color(t_point p, double m_radius,
							t_mm_scale sc);
t_mm_scale				get_minimap_scale(t_game *g, double radius);
int						get_minimap_pixel_color(t_game *g, double rx, double ry,
							t_mm_scale sc);
void					get_icone_info(t_circle *icn, t_circle minimap,
							double icon_angle, double player_angle);
bool					angle_between(double angle, double start, double end);

void					handle_exit(t_game *game);
t_door					get_door(int x, int y);

int						mouse_move_handler(int x, int y, t_game *game);
void					put_timer_imag(t_game *game, t_timer *img_info);
void					draw_timer(t_game *game, int sign);
void					put_timer_pixel(t_game *game, int x, int y, int color);
void					put_timer_bg(t_game *game, t_image *img);
void					put_timer_bg(t_game *game, t_image *img);
void					put_timer_pixel(t_game *game, int x, int y, int color);
void					put_timer_pixel(t_game *game, int x, int y, int color);
int						get_size_lines_of_map(t_fcub *fcub);
void					flood_fill(t_fcub *fcub, int rows, int colums);
int						mouse_move(int x, int y, t_game *game);
int						mouse_click(int code, int x, int y, t_game *game);
void					dup_map(t_fcub *fcub, char **map);
void					free_map_flood_fill(char **map);
int						count_char_in_map(char **map, char c);
void					next(t_fcub *fcub, int x, int y, int *door);
void					handel_o_press(t_game *game);
void					restart_game(t_game *game);
void					init_resources_game(t_game *game);

t_mm_scale				get_minimap_scale(t_game *g, double radius);

bool					in_border(t_point f, t_mm_scale sc);

bool					in_door(t_point f, t_map map, int row, int col);
t_point					calc_world_point(t_game *g, double rx, double ry,
							t_mm_scale sc);

int						get_out_of_bounds_color(t_game *g, int row, int col);

bool					valid_door_pos(double new_x, double new_y);
void					init_image(t_game *game, t_image *img, char *path);

double					get_view_angel(char dir);

double					correct_dist(double raw_d, double ang);
void					lunch_cube(t_game *game);
void					update_portal_animation(t_game *g,
							long long current_time);
void					update_doors_in_range(void);
void					update_single_door_in_range(t_door *door,
							t_point player_pos, double player_angle,
							char **map);
bool					check_vertical_door(t_door *door, t_point p_pos,
							double player_angle, t_point door_center);
bool					handle_video(char *path, t_video *vid);
bool					check_horizontal_door(t_door *door, t_point p_pos,
							double player_angle, t_point door_center);
bool					is_door_close_enough(t_point p_pos, t_point door_center,
							bool horizontal);
bool					is_horizontal_door(t_door *door, char **map);
bool					angle_between(double angle, double start, double end);
void					reste_door_rang(t_game *game);
bool					update_doors_states(t_game *game);
bool					check_exit_door(t_game *g, long long current_time);
bool					looking_at_open_portal(t_game *g);
bool					sweep_fov_for_door(t_game *g, double player_angle,
							double p1_angle, double p2_angle);
void					get_exit_door_corners(t_door *door, char **map,
							t_point *p1, t_point *p2);
bool					is_exit_door_horizontal(t_door *door, char **map);
void					update_closing_door(t_door *door,
							long long current_time);
void					update_opening_door(t_door *door,
							long long current_time);
void					handel_o_press(t_game *game);
void					start_opening_door(t_door *door);
void					start_closing_door(t_door *door);
bool					door_is_closed(t_door door);
void					print_err(char *msg);
long long				get_current_time_ms(void);
void					parse_input(t_game *game, int ac, char **av);
int						get_rgb(t_fcub *fcub, char *color);
void					init_image2(t_game *game, t_image *img, char *path);

#endif
