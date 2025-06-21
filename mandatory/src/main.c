#include "cub.h"

bool	is_valid_dir(char dir)
{
	if (dir == 'N' || dir == 'S' || dir == 'E' || dir == 'W')
		return (true);
	return (false);
}

void	init_player(t_game *game)
{
	int		y;
	int		x;
	char	**map;

	map = game->map->arr;
	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (is_valid_dir(map[y][x]))
			{
				game->player.x = (x + 0.5) * TILE_SIZE;
				game->player.y = (y + 0.5) * TILE_SIZE;
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
	game->mlx = mlx_init();
	if (!game->mlx)
		print_err("Failed to initialize MLX\n");
	game->win = mlx_new_window(game->mlx, WIN_WIDTH, WIN_HEIGHT, "Cub3D");
	if (!game->win)
		print_err("Failed to create window\n");
	init_player(&game);
	init_image_fram(&game, &game->map->map_buf);
	init_image_fram(&game, &game->player_view_buf);
	init_image(&game, &game->graphics[E_WALL], "textures/east_wall.xpm");
	init_image(&game, &game->graphics[N_WALL], "textures/north_wall.xpm");
	init_image(&game, &game->graphics[W_WALL], "textures/west_wall.xpm");
	init_image(&game, &game->graphics[S_WALL], "textures/south_wall.xpm");
}

int	main(int ac, char **av)
{
	t_game *game;
	parse_input(game, ac, av);// check file and map and get maps values  , and store it in array of maps
	intilize_game_resorces(game);
    lunch_game_hooks();
}