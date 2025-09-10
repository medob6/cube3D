/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbousset <mbousset@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 09:38:33 by omben-ch          #+#    #+#             */
/*   Updated: 2025/09/10 09:07:07 by mbousset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycaster.h"

void	parse_input(t_game *game, int ac, char **av)
{
	t_fcub	fcub;

	parse_and_get_data(&fcub, ac, av);
	game->data.paths[N_WALL] = fcub.n_path;
	game->data.paths[W_WALL] = fcub.w_path;
	game->data.paths[E_WALL] = fcub.e_path;
	game->data.paths[S_WALL] = fcub.s_path;
	game->data.ceiling_clr = get_rgb(&fcub, fcub.c_color);
	game->data.floor_clr = get_rgb(&fcub, fcub.f_color);
	game->data.map.arr = fcub.map;
	game->data.map.map_h = count_list(fcub.map);
	game->data.map.map_w = get_size_of_long_line(&fcub);
}

void	print_err(char *msg)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(msg, 2);
	cleanup(EXIT_FAILURE);
}

int	game_loop(t_game *game)
{
	if (game->player.moving)
	{
		display_scean(game);
		draw_mini_map(game);
		mlx_put_image_to_window(game->mlx, game->win, game->display.img, 0, 0);
	}
	// if (get_key(KEY_O,game)->press)
	// {
	// 	if (game->data.map.arr[(int)game->player.p.y][(int)game->player.p.x + 1] == 'D')
	// 		game->data.map.arr[(int)game->player.p.y][(int)game->player.p.x + 1] = '0';
	// 	else if (game->data.map.arr[(int)game->player.p.y][(int)game->player.p.x - 1] == 'D')
	// 		game->data.map.arr[(int)game->player.p.y][(int)game->player.p.x - 1] == '0';
	// 	else if (game->data.map.arr[(int)game->player.p.y + 1][(int)game->player.p.x] == 'D')
	// 		game->data.map.arr[(int)game->player.p.y + 1][(int)game->player.p.x] == 'D';
	// 	else if (game->data.map.arr[(int)game->player.p.y - 1][(int)game->player.p.x] == 'D')
	// 		game->data.map.arr[(int)game->player.p.y - 1][(int)game->player.p.x] == 'D';
	// }
	update_player(game);
	handle_exit(game);
	return (1);
}

void	lunch_game_hooks(t_game *game)
{
	mlx_do_key_autorepeatoff(game->mlx);
	mlx_hook(game->win, 2, 1L << 0, key_press, game);
	mlx_hook(game->win, 3, 1L << 1, key_release, game);
	mlx_hook(game->win, 17, 0, handle_close, NULL);
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
	parse_input(game, ac, av);
	game->win = mlx_new_window(game->mlx, game->win_w, game->win_h, "Cub3D");
	if (!game->win)
		print_err("Failed to create window\n");
	initilize_game_resorces(game);
	lunch_game_hooks(game);
	return (0);
}
