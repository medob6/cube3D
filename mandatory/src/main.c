/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbousset <mbousset@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 15:39:43 by mbousset          #+#    #+#             */
/*   Updated: 2025/06/25 17:12:01 by mbousset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	print_map(t_map *map)
{
	int	i;

	i = 0;
	while (i < map->map_h)
	{
		printf("%s\n", map->arr[i++]);
	}
}

void	parse_input(t_game *game, int ac, char **av)
{
	int			i;
	static char	*dummy_map[] = {"11111111111", "10000000001", "10111111001",
			"10100001001", "10101101001", "10001000001", "10101011101",
			"10101010001", "10001010E01", "10111111101", "11111111111"};

	(void)ac;
	(void)av;
	i = 0;
	game->data.map.map_h = sizeof(dummy_map) / sizeof(dummy_map[0]);
	game->data.map.map_w = ft_strlen(dummy_map[0]);
	game->data.map.arr = malloc(sizeof(char *) * (game->data.map.map_h + 1));
	while (i < game->data.map.map_h)
	{
		game->data.map.arr[i] = ft_strdup(dummy_map[i]);
		i++;
	}
	game->data.map.arr[i] = NULL;
	print_map(&game->data.map);
	game->data.paths[E_WALL] = "./textures/east.xpm";
	game->data.paths[W_WALL] = "./textures/west.xpm";
	game->data.paths[N_WALL] = "./textures/north.xpm";
	game->data.paths[S_WALL] = "./textures/south.xpm";
	game->data.ceiling_clr = 0x87CEEB;
	game->data.floor_clr = 0x2E2E2E;
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
	game->player.moving = true;
	if (game->player.moving)
	{
		// cast_rays(game);
		// draw_3d_view(game);
		draw_mini_map(game);
		// draw_player(game);
	}
	mlx_put_image_to_window(game->mlx, game->win, game->display.img, 0, 0);
	return (1);
}

void	lunch_game_hooks(t_game *game)
{
	mlx_do_key_autorepeatoff(game->mlx);
	mlx_hook(game->win, 2, 1L << 0, key_press, game);
	mlx_hook(game->win, 3, 1L << 1, key_release, game);
	mlx_loop_hook(game->mlx, game_loop, game);
	mlx_loop(game->mlx);
}

int	main(int ac, char **av)
{
	t_game	*game;

	game = get_game();
	game->mlx = mlx_init();
	if (!game->mlx)
		print_err("Failed to initialize MLX\n");
	get_window_dimensions();
	game->win = mlx_new_window(game->mlx, game->win_w, game->win_h, "Cub3D");
	if (!game->win)
		print_err("Failed to create window\n");
	parse_input(game, ac, av);
	initilize_game_resorces(game);
	lunch_game_hooks(game);
	return (0);
}
