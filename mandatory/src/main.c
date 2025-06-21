#include "cub.h"

void	parse_input(t_game *game, int ac, char **av)
{
	static char	*dummy_map[] = {"11111", "1N001", "10001", "10001", "11111",
			NULL};

	(void)ac;
	(void)av;
	game->data.paths[E_WALL] = "./textures/east.xpm";
	game->data.paths[W_WALL] = "./textures/west.xpm";
	game->data.paths[N_WALL] = "./textures/north.xpm";
	game->data.paths[S_WALL] = "./textures/south.xpm";
	game->data.ceiling_clr = 0x87CEEB;
	game->data.floor_clr = 0x2E2E2E;
	game->data.map.arr = dummy_map;
	game->data.map.map_h = 5;
	game->data.map.map_w = 5;
}

void	print_err(char *msg)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(msg, 2);
	cleanup(get_game(), EXIT_FAILURE);
}

int	game_loop(t_game *game)
{
	update_player(game);
	// draw_map(game);
	// draw_player(game);
	// draw_rays(game);
	// draw_3d_view(game);
	mlx_put_image_to_window(game->mlx, game->win, game->display.img, 0, 0);
	return (1);
}

void	lunch_game_hooks(t_game *game)
{
	mlx_do_key_autorepeatoff(game->mlx);
	mlx_hook(game->win, 2, 1L << 0, key_press, &game);
	mlx_hook(game->win, 3, 1L << 1, key_release, &game);
	mlx_loop_hook(game->mlx, game_loop, &game);
	mlx_loop(game->mlx);
}

int	main(int ac, char **av)
{
	t_game	*game;

	game = get_game();
	game->mlx = mlx_init();
	if (!game->mlx)
		print_err("Failed to initialize MLX\n");
	game->win = mlx_new_window(game->mlx, WIN_WIDTH, WIN_HEIGHT, "Cub3D");
	if (!game->win)
		print_err("Failed to create window\n");
	parse_input(game, ac, av);
	initilize_game_resorces(game);
	lunch_game_hooks(game);
	return (0);
}
