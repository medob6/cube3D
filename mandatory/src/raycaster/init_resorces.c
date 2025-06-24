#include "cub.h"

t_game	*get_game(void)
{
	static t_game	game;

	return (&game);
}

bool	is_valid_dir(char dir)
{
	if (dir == 'N' || dir == 'S' || dir == 'E' || dir == 'W')
		return (true);
	return (false);
}

double	deg_to_rad(double a)
{
	return (a * M_PI / 180.0);
}

double	get_view_angel(char dir)
{
	if (dir == 'E')
		return (deg_to_rad(0));
	else if (dir == 'N')
		return (deg_to_rad(90));
	else if (dir == 'W')
		return (deg_to_rad(180));
	else if (dir == 'S')
		return (deg_to_rad(270));
	return (1);
}

void	init_image_fram(t_game *game, t_image *frame)
{
	frame->img = mlx_new_image(game->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!frame->img)
		print_err("Failed to create image");
	frame->addr = mlx_get_data_addr(frame->img, &frame->bpp, &frame->line_len,
			&frame->endian);
	if (!frame->addr)
		print_err("Failed to get image data address");
}

void	init_image(t_game *game, t_image *img, char *path)
{
	img->img = mlx_xpm_file_to_image(game->mlx, path, &img->w, &img->h);
	if (!img->img)
	{
		perror("Error: Failed to load an image ");
		exit(1);
	}
	img->addr = mlx_get_data_addr(img->img, &img->bpp, &img->line_len,
			&img->endian);
}

void	init_player(t_game *game)
{
	int		y;
	int		x;
	char	**map;

	map = game->data.map.arr;
	game->player.moving = false;
	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (is_valid_dir(map[y][x]))
			{
				game->player.p.x = (x + 0.5) * TILE_SIZE;
				game->player.p.y = (y + 0.5) * TILE_SIZE;
				game->player.angle = get_view_angel(map[y][x]);
				return ;
			}
			x++;
		}
		y++;
	}
}

void	initilize_game_resorces(t_game *game)
{
	init_keys(game);
	init_player(game);
	init_image_fram(game, &game->display);
	init_image(game, &game->graphics[E_WALL], game->data.paths[E_WALL]);
	init_image(game, &game->graphics[N_WALL], game->data.paths[N_WALL]);
	init_image(game, &game->graphics[W_WALL], game->data.paths[W_WALL]);
	init_image(game, &game->graphics[S_WALL], game->data.paths[S_WALL]);
	init_image(game, &game->graphics[N_ICONE], "textures/N_icon.xpm");
	init_image(game, &game->graphics[ARROW], "textures/minimap_player.xpm");
}
