#ifndef CUB_H
# define CUB_H
# include "get_next_line.h"
# include "libft.h"
# include "parser.h"
# include <errno.h>
# include <fcntl.h>
# include <math.h>
# include <mlx.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

// window config
# define WIN_WIDTH 1800
# define WIN_HEIGHT 1500
# define TILE_SIZE 100

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

// speed
# define MOVE_SPEED 5
# define ROTATE_SPEED 0.05

// player config
# define FIELD_SIGHT 170
# define NUM_RAYS WIN_WIDTH
# define FOV_ANGLE M_PI / 3

typedef enum e_graphic
{
	E_WALL,
	N_WALL,
	W_WALL,
	S_WALL,
	N_ICONE,
	ARROW,

}				t_graphic;

typedef struct s_point
{
	double		x;
	double		y;
	double		z;
}				t_point;

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
	t_player	player;
	t_image		graphics[6];
	t_image		display;
	t_data		data;
	t_key		keys[9];
}				t_game;

int				handle_close(t_game *game);
void			cleanup(t_game *game, int code);
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
double			get_distance(t_point a, t_point b);

//! Ray caster functions :



#endif
