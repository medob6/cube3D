/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbousset <mbousset@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 09:38:33 by omben-ch          #+#    #+#             */
/*   Updated: 2025/07/31 10:06:57 by mbousset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycaster_bs.h"
#include "video_bs.h"

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

// lets add door logic and player sprite animation

void	print_err(char *msg)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(msg, 2);
	cleanup(EXIT_FAILURE);
}

bool	try_open_door(t_game *game)
{
	int	x;
	int	y;
	int	map_width;
	int	map_height;

	x = (int)(game->player.p.x / WALL_WIDTH);
	y = (int)(game->player.p.y / WALL_WIDTH);
	map_width = game->data.map.map_w;
	map_height = game->data.map.map_h;
	// Check right
	if (x + 1 < map_width && game->data.map.arr[y][x + 1] == 'D')
		game->data.map.arr[y][x + 1] = '0';
	// Check left
	else if (x - 1 >= 0 && game->data.map.arr[y][x - 1] == 'D')
		game->data.map.arr[y][x - 1] = '0';
	// Check down
	else if (y + 1 < map_height && game->data.map.arr[y + 1][x] == 'D')
		game->data.map.arr[y + 1][x] = '0';
	// Check up
	else if (y - 1 >= 0 && game->data.map.arr[y - 1][x] == 'D')
		game->data.map.arr[y - 1][x] = '0';
	else if (game->data.map.arr[y][x] == 'D')
		game->data.map.arr[y][x] = '0';
	else
		return (false);
	return (true);
}

int	game_loop(t_game *game)
{
	static bool	start = true;
	static int	video_result = 0;

	if (start)
	{
		start = false;
		video_result = play_video("bonus/video/intro.mp4");
		if (video_result == 1)
		{
			usleep(30000);
			start = false;
		}
		else if (video_result == -1)
		{
			usleep(300000);
			printf("err while procceig video file , dispalying menu ... \n");
			start = false;
		}
	}
	else
	{
		if (game->player.moving)
		{
			display_scean(game);
			draw_mini_map(game);
			mlx_put_image_to_window(game->mlx, game->win, game->display.img, 0,
				0);
		}
		update_player(game);
		if (get_key(KEY_O, game)->press)
		{
			game->player.moving = game->player.moving || try_open_door(game);
		}
	}
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

// TODO:

// DOOR :

// DOOR COLISION fixed
// DOOR RAYCASTING fixed
// DOOR dedection not fixed
// DOOR if door open a littel bet not fixed
// DOOR animation not fixed
// DOOR in minimap
// DOOR CHECK beteen two walls in parsing not fixed  // for omar

// 