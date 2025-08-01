/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omben-ch <omben-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 09:38:33 by omben-ch          #+#    #+#             */
/*   Updated: 2025/08/01 16:53:09 by omben-ch         ###   ########.fr       */
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

int	mouse_move(int x, int y, t_game *game)
{
	int button;
	int i;

	i = -1;
	button = check_button(game,x,y);
	while (++i < NB_BUTTON)
		game->buttons[i].on_hover(game,button);
	draw_menu(game);
	return 0;
}

int	game_loop(t_game *game)
{
	if (game->player.moving)
	{
		display_scean(game);
		draw_mini_map(game);
		mlx_put_image_to_window(game->mlx, game->win, game->display.img, 0, 0);
	}
	update_player(game);
	return (1);
}

int mouse_click(int code, int x,int y ,t_game *game)
{
	int button;
	int i;

	i = -1;
	button = check_button(game,x,y);
	if (code == 1)
	{
		while (++i < NB_BUTTON)
			game->buttons[i].on_click(game, button);
		draw_menu(game);
	}
	return (0);
}

void	lunch_game_hooks(t_game *game)
{
	init_img_menu(game);
	draw_menu(game);
	mlx_do_key_autorepeatoff(game->mlx);
	mlx_hook(game->win, 2, 1L << 0, key_press, game);
	mlx_hook(game->win, 3, 1L << 1, key_release, game);
	mlx_hook(game->win, 6, 1L << 6, mouse_move, game);
	mlx_mouse_hook(game->win,mouse_click,game);
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
