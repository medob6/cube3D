/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omben-ch <omben-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 09:38:33 by omben-ch          #+#    #+#             */
/*   Updated: 2025/09/18 18:56:40 by omben-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycaster_bs.h"
#include "video_bs.h"

int	play_win_lose_vid(t_game *game)
{
	if (game->win_lose == 1)
	{
		game->end_start_menu = IN_PLY_W_VID;
		if (handle_video("bonus/video/you_win.mkv", &game->videos[WIN]))
			return (1);
		restart_game(game);
		return (1);
	}
	if (game->win_lose == 2)
	{
		game->end_start_menu = IN_PLY_L_VID;
		if (handle_video("bonus/video/game_over.mkv", &game->videos[LOSE]))
			return (1);
		restart_game(game);
		return (1);
	}
	return (0);
}

void	game_runing(t_game *game)
{
	bool	scean_changed;
	bool	door_moving;

	handle_exit(game);
	door_moving = update_doors_states(game);
	scean_changed = game->player.moving || door_moving;
	handel_o_press(game);
	update_player(game);
	if (game->player.moving)
		update_doors_in_range();
	update_portal_animation(game, get_current_time_ms());
	if (game->passed)
	{
		game->win_lose = 1;
		return ;
	}
	if (scean_changed)
		lunch_cube(game);
	draw_timer(game, 0);
}

int	game_loop(t_game *game)
{
	if (handle_video("bonus/video/cub3d_intro.mkv", &game->videos[INTRO]))
		return (1);
	if (play_win_lose_vid(game))
		return (1);
	draw_menu(game);
	if (game->end_start_menu == IN_GAME)
		game_runing(game);
	return (1);
}

void	lunch_game_hooks(t_game *game)
{
	init_img_menu(game);
	game->end_start_menu = IN_PLY_I_VID;
	game->win_lose = 0;
	mlx_do_key_autorepeatoff(game->mlx);
	mlx_hook(game->win, 2, 1L << 0, key_press, game);
	mlx_hook(game->win, 3, 1L << 1, key_release, game);
	mlx_hook(game->win, 17, 0, handle_close, NULL);
	mlx_hook(game->win, 6, 1L << 6, mouse_move, game);
	mlx_mouse_hook(game->win, mouse_click, game);
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
	game->win = mlx_new_window(game->mlx, game->win_w, game->win_h,
			"FIND THE EXIT");
	if (!game->win)
		print_err("Failed to create window\n");
	initilize_game_resorces(game);
	lunch_game_hooks(game);
	return (0);
}
