/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omben-ch <omben-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 09:38:33 by omben-ch          #+#    #+#             */
/*   Updated: 2025/07/26 18:16:21 by omben-ch         ###   ########.fr       */
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

int	mouse_move(int x, int y, void *param)
{
	t_game	*game;
	
	game = (t_game *)param;
	(void)game;
	if ((x >= game->list[0].start_x && x <= game->list[0].end_x)
		&& (y >= game->list[0].start_y && y <= game->list[0].end_y))
			game->list[0].img = &game->graphics[H_START];
	else
		game->list[0].img = &game->graphics[START];
	if ((x >= game->list[1].start_x && x <= game->list[1].end_x)
		&& (y >= game->list[1].start_y && y <= game->list[1].end_y))
		game->list[1].img = &game->graphics[H_CONTROL];
	else
		game->list[1].img = &game->graphics[CONTROL];
	if ((x >= game->list[2].start_x && x <= game->list[2].end_x)
		&& (y >= game->list[2].start_y && y <= game->list[2].end_y))
		game->list[2].img = &game->graphics[H_EXIT];
	else
		game->list[2].img = &game->graphics[EXIT];
	put_bg(game, &game->graphics[BG]);	
	put_imag(game, &game->list[0]);
	put_imag(game, &game->list[1]);
	put_imag(game, &game->list[2]);
	mlx_put_image_to_window(game->mlx, game->win, game->display.img, 0, 0);
	return 0;
}

int	game_loop(t_game *game)
{
	init_img_menu(game);
	put_bg(game, &game->graphics[BG]);
	put_imag(game, &game->list[0]);
	put_imag(game, &game->list[1]);
	put_imag(game, &game->list[2]);
	mlx_put_image_to_window(game->mlx, game->win, game->display.img, 0, 0);
	// if (game->player.moving)
	// {
	// 	display_scean(game);
	// 	draw_mini_map(game);
	// 	mlx_put_image_to_window(game->mlx, game->win, game->display.img, 0, 0);
	// }
	// update_player(game);
	return (1);
}

void	lunch_game_hooks(t_game *game)
{
	mlx_do_key_autorepeatoff(game->mlx);
	mlx_hook(game->win, 2, 1L << 0, key_press, game);
	mlx_hook(game->win, 3, 1L << 1, key_release, game);
	mlx_hook(game->win, 6, 1L << 6, mouse_move, game);
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
