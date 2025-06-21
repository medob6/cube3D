#ifndef CUB_H
# define CUB_H
# include "get_next_line.h"
# include "libft.h"
# include "parser.h"
# include <errno.h>
# include <fcntl.h>
# include <mlx.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <stdbool.h>

// window config
# define WIN_WIDTH 1100
# define WIN_HEIGHT 1100
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
# define ROTATE_SPEED 0.1

// player config
# define FIELD_SIGHT 170
# define NUM_RAYS WIN_WIDTH
# define FOV_ANGLE deg_to_rad(60)

// t_image

enum			graphics
{
	E_WALL,
	N_WALL,
	W_WALL,
	S_WALL,

};

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

typedef struct
{
	t_image		player;
	double		x;
	double		y;
	double		angle;
}				t_player;

typedef struct s_map
{
	char		**arr;
	int			map_w;
	int			map_h;
	t_image		map_buf;
}				t_map;

typedef struct s_game
{
	void		*mlx;
	void		*win;
	t_player	player;
	t_image		*graphics;
	t_image		display; // what player see
	t_map		*map;

}				t_game;

#endif


//
//
//
// [' ','1','1','1','1','1',' ',' ',' ',',',' ',' ',' ']
// ['1','0','0','0','0','0','1',' ',' ',',',' ',' ',' ']
// ['1','0','0','0','E','0','1',' ',' ',',','1','1','1']
// ['1','1','1','1','1','1','1',' ',' ',',','1','0','1']
// [' ',' ',' ',' ',' ',' ',' ',' ',' ',',','1','1','1']
//
//
//
// if (cher == '0' && ( (j == 0 || j == last_arr_indx ) || (i == 0 || i == east_edge)))
//         then "not valid map"
// else if (cher == '0' &&  cher_up[i-1][i] == ' ' || cher_down[j+1][i] == ' ' || cher_est[j][i+1] == ' ' || cher_west[j][i-1] == ' ')
//         then  "not valid"
//
//
//

// 1111111
// 1     1
// 1 111 1
// 1 1E1 1
// 1 110 1
// 1   1
// 1111111


