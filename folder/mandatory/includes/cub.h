/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbousset <mbousset@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 15:39:51 by mbousset          #+#    #+#             */
/*   Updated: 2025/07/30 11:31:57 by mbousset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H
# include "get_next_line.h"
# include "libft.h"
# include "parser.h"
# include <X11/keysymdef.h>
# include <errno.h>
# include <fcntl.h>
# include <math.h>
# include <mlx.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

# define WALL_HIGHT 64
# define WALL_WIDTH 128

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
# define MOVE_SPEED 5
# define ROTATE_SPEED 0.01
# define JUMP_SPEED 10
# define M_PI_3 1.0471975511965976
# define FOV_ANGLE M_PI_3

// minimp
# define MINIMAP_SCREEN_SCALE 0.09
# define ICON_SCALE 0.14
# define PLAYER_SCALE 0.20

typedef enum e_graphic
{
	E_WALL,
	N_WALL,
	W_WALL,
	S_WALL,
	DOOR,
	N_ICONE,
	ARROW,
}				t_graphic;

typedef struct s_point
{
	double		x;
	double		y;
	double		z;
}				t_point;

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
}				t_image;

typedef struct s_player
{
	t_image		sprite;
	t_point		p;
	double		angle;
	double		hieght;
	bool		moving;
	bool		jumping;
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

typedef struct s_game
{
	void		*mlx;
	void		*win;
	int			win_h;
	int			win_w;
	t_data		data;
	t_player	player;
	t_key		keys[11];
	t_image		graphics[7];
	t_image		display;
}				t_game;

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

/* FUNCTIONS */
void			play_intro(char *path);

#endif
