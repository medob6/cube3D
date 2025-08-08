/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbousset <mbousset@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 09:38:33 by omben-ch          #+#    #+#             */
/*   Updated: 2025/08/08 19:06:35 by mbousset         ###   ########.fr       */
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
	game->doors = fcub.door;
	game->nb_of_doors = fcub.nb_door;
}

void	print_err(char *msg)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(msg, 2);
	cleanup(EXIT_FAILURE);
}

// bool	open_door(t_game *game)
// {
// 	int	x;
// 	int	y;
// 	int	map_width;
// 	int	map_height;

// 	x = game->player.door_x;
// 	y = game->player.door_y;
// 	map_width = game->data.map.map_w;
// 	map_height = game->data.map.map_h;
// 	if (x < map_width && map_height > y && game->data.map.arr[y][x] == 'D')
// 		game->data.map.arr[y][x] = '0';
// 	else
// 		return (false);
// 	return (true);
// }

// void	draw_vert_line(t_image *img, int x, int len)
// {
// 	int	y;

// 	y = 0;
// 	while (y <= len)
// 	{
// 		printf("x == %d\n", x);
// 		my_mlx_pixel_put(*img, x, y, 0xFF0000);
// 		y++;
// 	}
// }

#include <math.h> // If needed for cos/sin
#include <stdbool.h> // For bool type
#include <stdio.h> // For printf
#include <sys/time.h> // For gettimeofday
#include <unistd.h> // For usleep

long	get_time_diff_ms(struct timeval *last)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	return ((now.tv_sec - last->tv_sec) * 1000L + (now.tv_usec - last->tv_usec)
		/ 1000L);
}


void	update_door_animation(t_game *game, t_door *door)
{
	long	elapsed;

	const int frame_interval_ms = 300; // 30 FPS
	if (door->opening || door->closing)
	{
		elapsed = get_time_diff_ms(&door->last_update);
		if (elapsed >= frame_interval_ms)
		{
			gettimeofday(&door->last_update, NULL); // reset timer
			if (door->opening)
			{
				game->player.moving = true;
				door->closing = false;
				if (door->frame < 8)
					door->frame++;
				else
					door->opening = false;
			}
			else if (door->closing)
			{
				game->player.moving = true;
				if (door->frame > 0)
					door->frame--;
				else
					door->closing = false;
			}
		}
	}
}


int	game_loop(t_game *game)
{
	static bool	start = true;
	static int	video_result = 0;
	int			n;

	if (start)
	{
		start = false; // this line should be removed
		video_result = play_video("bonus/video/intro.mp4");
		if (video_result == 1)
		{
			usleep(30000);
			start = false;
		}
		else if (video_result == -1)
		{
			usleep(300000);
			printf("err while processing video file, displaying menu...\n");
			start = false;
		}
	}
	else
	{
		if (game->player.moving)
		{
			n = -1;
			while (++n < game->nb_of_doors)
				game->doors[n].open = false;
			display_scean(game);
			draw_mini_map(game);
			mlx_put_image_to_window(game->mlx, game->win, game->display.img, 0,
				0);
		}
		update_player(game);
		if (get_key(KEY_O, game)->press)
		{
			n = 0;
			while (n < game->nb_of_doors)
			{
				if (game->doors[n].open && game->doors[n].frame == 8)
				{
					// Close only if not already closing
					if (!game->doors[n].closing)
					{
						game->doors[n].closing = true;
						game->doors[n].opening = false;
					}
				}
				else if (game->doors[n].open && !game->doors[n].closing
					&& !game->doors[n].opening)
				{
					// Open only if not already opening or closing
					game->doors[n].opening = true;
					game->doors[n].closing = false;
				}
				n++;
			}
		}
		// 🔄 Animate all doors with real-time-based animation
		n = 0;
		while (n < game->nb_of_doors)
		{
			update_door_animation(game, &game->doors[n]);
			n++;
		}
	}
	handle_exit(game);
	return (1);
}

// int	game_loop(t_game *game)
// {
// 	static bool	start = true;
// 	static int	video_result = 0;
// 	static int	i = 0;
// 	int			n;

// 	if (start)
// 	{
// 		start = false;
// 		video_result = play_video("bonus/video/intro.mp4");
// 		if (video_result == 1)
// 		{
// 			usleep(30000);
// 			start = false;
// 		}
// 		else if (video_result == -1)
// 		{
// 			usleep(300000);
// 			printf("err while procceig video file , dispalying menu ... \n");
// 			start = false;
// 		}
// 	}
// 	else
// 	{
// 		if (game->player.moving)
// 		{
// 			n = -1;
// 			while (++n < game->nb_of_doors)
// 				game->doors[n].open = false;
// 			display_scean(game);
// 			draw_mini_map(game);
// 			mlx_put_image_to_window(game->mlx, game->win, game->display.img, 0,
// 				0);
// 		}
// 		update_player(game);
// 		if (get_key(KEY_O, game)->press)
// 		{
// 			n = 0;
// 			while (n < game->nb_of_doors)
// 			{
// 				if (game->doors[n].open && game->doors[n].frame == 8)
// 				{
// 					game->doors[n].closing = true;
// 				}
// 				else if (game->doors[n].open)
// 				{
// 					game->doors[n].opening = true;
// 				}
// 				n++;
// 			}
// 		}
// 		n = 0;
// 		while (n < game->nb_of_doors)
// 		{
// 			if (game->doors[n].opening)
// 			{
// 				game->player.moving = true;
// 				game->doors[n].closing = false;
// 				if (i++ % 80 == 0)
// 				{
// 					if (game->doors[n].frame < 8)
// 						game->doors[n].frame++;
// 					else
// 						game->doors[n].opening = false;
// 				}
// 			}
// 			else if (game->doors[n].closing)
// 			{
// 				game->player.moving = true;
// 				if (i++ % 80 == 0)
// 				{
// 					if (game->doors[n].frame > 0)
// 						game->doors[n].frame--;
// 					else
// 						game->doors[n].closing = false;
// 				}
// 			}
// 			n++;
// 		}
// 	}
// 	handle_exit(game);
// 	return (1);
// }

// static bool handle_intro_video(void)
// {
// 	static bool	start = true;
// 	static int	video_result = 0;

// 	if (!start)
// 		return (false);

// 	start = false;
// 	video_result = play_video("bonus/video/intro.mp4");

// 	if (video_result == 1)
// 		usleep(30000);
// 	else if (video_result == -1)
// 	{
// 		usleep(300000);
// 		printf("err while processing video file, displaying menu...\n");
// 	}
// 	return (true);
// }

// static void handle_player_movement(t_game *game)
// {
// 	int	n;

// 	if (!game->player.moving)
// 		return ;

// 	for (n = 0; n < game->nb_of_doors; ++n)
// 		game->doors[n].open = false;

// 	display_scean(game);
// 	// draw_mini_map(game);
// 	mlx_put_image_to_window(game->mlx, game->win, game->display.img, 0, 0);
// }

// static void handle_door_interaction(t_game *game)
// {
// 	int	n = 0;

// 	if (!get_key(KEY_O, game)->press)
// 		return ;

// 	while (n < game->nb_of_doors)
// 	{
// 		if (game->doors[n].open && game->doors[n].frame == 8)
// 			game->doors[n].closing = true;
// 		else if (game->doors[n].open)
// 			game->doors[n].opening = true;
// 		n++;
// 	}
// }

// static void animate_doors(t_game *game)
// {
// 	static int	i = 0;
// 	int			n = 0;

// 	while (n < game->nb_of_doors)
// 	{
// 		if (game->doors[n].opening)
// 		{
// 			game->player.moving = true;
// 			if (i++ % 10 == 0)
// 			{
// 				if (game->doors[n].frame < 8)
// 					game->doors[n].frame++;
// 				else
// 					game->doors[n].opening = false;
// 			}
// 		}
// 		if (game->doors[n].closing)
// 		{
// 			game->player.moving = true;
// 			if (i++ % 10 == 0)
// 			{
// 				if (game->doors[n].frame > 0)
// 					game->doors[n].frame--;
// 				else
// 					game->doors[n].closing = false;
// 			}
// 		}
// 		n++;
// 	}
// }

// int	game_loop(t_game *game)
// {
// 	if (handle_intro_video())
// 		return (1);

// 	handle_player_movement(game);
// 	update_player(game);
// 	handle_door_interaction(game);
// 	animate_doors(game);
// 	handle_exit(game);

// 	return (1);
// }

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
// DOOR dedection fixed
// DOOR if door open  fixed

// DOOR animation not fixed
// DOOR in minimap

// DOOR CHECK beteen two walls in parsing not fixed  // for omar
// DOOR

//

// today i should fix door animation best way possible