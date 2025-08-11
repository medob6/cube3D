/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbousset <mbousset@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 09:38:33 by omben-ch          #+#    #+#             */
/*   Updated: 2025/08/11 10:16:14 by mbousset         ###   ########.fr       */
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
long long	get_current_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (long long)(tv.tv_sec) * 1000 + (tv.tv_usec / 1000);
}

void	print_err(char *msg)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(msg, 2);
	cleanup(EXIT_FAILURE);
}

static bool	handle_intro_video(void)
{
	static bool	start = true;
	static int	video_result = 0;

	if (!start)
		return (false);
	video_result = play_video("bonus/video/intro.mp4");
	if (video_result == 1)
	{
		start = false;
		usleep(30000);
	}
	else if (video_result == -1)
	{
		usleep(30000);
		printf("Error:\n err while processing video n");
	}
	return (true);
}

bool	door_is_closed(t_door door)
{
	int	last_fram;

	last_fram = get_game()->graphics[DOOR].frames;
	last_fram = 8; // in this case 10 becus te image is not fixed
	if (door.frame == last_fram)
		return (true);
	return (false);
}

static void	start_closing_door(t_door *door)
{
	door->closing = true;
	door->last_update = get_current_time_ms();
}

static void	start_opening_door(t_door *door)
{
	door->opening = true;
	door->last_update = get_current_time_ms();
}

void	handel_o_press(t_game *game)
{
	t_door	*door;

	if (!get_key(KEY_O, game)->press)
		return ;
	for (int n = 0; n < game->nb_of_doors; n++)
	{
		door = &game->doors[n];
		if (door->in_range && door_is_closed(*door))
			start_closing_door(door);
		else if (door->in_range)
			start_opening_door(door);
	}
}

static void	update_opening_door(t_door *door, long long current_time)
{
	door->closing = false;
	if (current_time - door->last_update >= FRAME_DURATION_MS)
	{
		if (door->frame < 8)
		{
			door->frame++;
			door->last_update = current_time;
		}
		else
		{
			door->opening = false;
		}
	}
}

static void	update_closing_door(t_door *door, long long current_time)
{
	if (current_time - door->last_update >= FRAME_DURATION_MS)
	{
		if (door->frame > 0)
		{
			door->frame--;
			door->last_update = current_time;
		}
		else
		{
			door->closing = false;
		}
	}
}

bool	update_doors_states(t_game *game)
{
	bool		door_moves;
	long long	current_time;
	t_door		*door;

	door_moves = false;
	current_time = get_current_time_ms();
	for (int n = 0; n < game->nb_of_doors; n++)
	{
		door = &game->doors[n];
		if (door->opening)
		{
			door_moves = true;
			update_opening_door(door, current_time);
		}
		else if (door->closing)
		{
			door_moves = true;
			update_closing_door(door, current_time);
		}
	}
	return (door_moves);
}

void	reste_door_rang(t_game *game)
{
	int	n;

	for (n = 0; n < game->nb_of_doors; n++)
		game->doors[n].in_range = false;
}

static void	update_doors_in_range(void)
{
	const t_game	*g = get_game();
	t_point			player_pos = g->player.p;
	double			player_angle = g->player.angle;
	char **map = g->data.map.arr;
	int i;

	i = -1;
	while (++i < g->nb_of_doors)
	{
		t_door	*door = &g->doors[i];

		bool door_is_horizontale = (map[(int)door->pos.y - 1][(int)door->pos.x] == '1');

		if (door_is_horizontale)
		{

			
			t_point door_center = {
				.x = (door->pos.x + 0.5) * WALL_WIDTH,
				.y = (door->pos.y + 0.5) * WALL_WIDTH};
			bool up = (player_pos.y < door_center.y);
			t_point door_p1 = {
				.x = (door->pos.x + 1 / 3) * WALL_WIDTH,
				.y = (door->pos.y + 0.5) * WALL_WIDTH};
			t_point door_p2 = {
				.x = (door->pos.x + 2 / 3) * WALL_WIDTH,
				.y = (door->pos.y + 0.5) * WALL_WIDTH};

			double dist = get_dist(door_center, player_pos);
			double dist_to_p1 = get_dist(door_p1, player_pos);
			double dist_to_p2 = get_dist(door_p2, player_pos);
			double vertical_dist = fabs(player_pos.y - door_center.y);
			bool close_enough = (vertical_dist < 3/2 *WALL_WIDTH) && ( door_center.x - WALL_WIDTH/2  < player_pos.x && player_pos.x <   door_center.x + WALL_WIDTH/2 );
			double p1_player_angle = asin((vertical_dist/dist_to_p1));
			double p2_player_angle = asin((vertical_dist/dist_to_p1));
			bool loking_at_door_center = player_angle > p1_player_angle && player_angle < p2_player_angle;
			door->in_range = (loking_at_door_center && close_enough);
		}

	}
}

int	game_loop(t_game *game)
{
	int		n;
	bool	scean_changed;
	bool	door_moving;

	handle_exit(game);
	// if (handle_intro_video())
	// 	return (1);
	door_moving = update_doors_states(game);
	scean_changed = game->player.moving || door_moving;
	handel_o_press(game);
	update_player(game);
	if (game->player.moving)
		update_doors_in_range();
	if (scean_changed)
	{
		display_scean(game);
		draw_mini_map(game);
		mlx_put_image_to_window(game->mlx, game->win, game->display.img, 0, 0);
	}
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
