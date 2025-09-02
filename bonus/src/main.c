/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omben-ch <omben-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 09:38:33 by omben-ch          #+#    #+#             */
/*   Updated: 2025/09/02 14:55:08 by omben-ch         ###   ########.fr       */
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
	game->exit = *fcub.exit;
	free(fcub.exit);
	game->passed = false;
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

// static bool	handle_video(char *path)
// {
// 	static bool	start = true;
// 	static int	video_result = 0;

// 	if (!start)
// 		return (false);
// 	video_result = play_video("bonus/video/intro.mp4");
// 	if (video_result == 1)
// 	{
// 		start = false;
// 		usleep(30000);
// 	}
// 	else if (video_result == -1)
// 	{
// 		usleep(30000);
// 		printf("Error:\n err while processing video n");
// 	}
// 	return (true);
// }

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
	if (game->exit.in_range && door_is_closed(game->exit))
		start_closing_door(&game->exit);
	else if (game->exit.in_range)
		start_opening_door(&game->exit);
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

bool		angle_between(double angle, double start, double end);

bool	looking_at_open_portal(t_game *g)
{
	t_point	player_pos;
	double	player_angle;
	char	**map;
	t_door	*door;
	bool	door_is_horizontale;
	t_point	door_center;
	t_point	door_p1;
	t_point	door_p2;
	double	p1_player_angle;
	double	p2_player_angle;
	double	angle;
	double	angle_step;
	int		x;

	player_pos = g->player.p;
	player_angle = g->player.angle;
	map = g->data.map.arr;
	door = &g->exit;
	// --- compute door orientation and corners ---
	door_is_horizontale = (map[(int)door->pos.y][(int)door->pos.x - 1] == '1'
			&& map[(int)door->pos.y][(int)door->pos.x + 1] == '1');
	door_center = (t_point){.x = (door->pos.x + 0.5) * WALL_WIDTH,
		.y = (door->pos.y + 0.5) * WALL_WIDTH};
	if (door_is_horizontale)
	{
		door_p1 = (t_point){.x = (door->pos.x) * WALL_WIDTH, .y = (door->pos.y
				+ 0.5) * WALL_WIDTH};
		door_p2 = (t_point){.x = (door->pos.x + 1) * WALL_WIDTH,
			.y = (door->pos.y + 0.5) * WALL_WIDTH};
	}
	else
	{
		door_p1 = (t_point){.x = (door->pos.x + 0.5) * WALL_WIDTH,
			.y = (door->pos.y) * WALL_WIDTH};
		door_p2 = (t_point){.x = (door->pos.x + 0.5) * WALL_WIDTH,
			.y = (door->pos.y + 1) * WALL_WIDTH};
	}
	// --- precompute door bounding angles relative to player ---
	p1_player_angle = normalize_angle(atan2(door_p1.y - player_pos.y, door_p1.x
				- player_pos.x));
	p2_player_angle = normalize_angle(atan2(door_p2.y - player_pos.y, door_p2.x
				- player_pos.x));
	// --- sweep through the FOV and check if door lies inside ---
	angle_step = FOV_ANGLE / (double)g->win_w;
	angle = player_angle - FOV_ANGLE / 2.0;
	x = -1;
	while (++x < g->win_w)
	{
		angle = normalize_angle(angle + angle_step);
		if (angle_between(angle, p1_player_angle, p2_player_angle))
			return (true);
	}
	return (false);
}

bool	check_exit_door(t_game *g, long long current_time)
{
	if (g->exit.frame == 8)
	{
		if (looking_at_open_portal(g))
			return (true);
		return (false);
	}
	if (g->exit.opening)
		update_opening_door(&g->exit, current_time);

	return (false);
	// return (true);
}

bool	update_doors_states(t_game *game)
{
	bool		door_moves;
	long long	current_time;
	t_door		*door;

	door_moves = false;
	current_time = get_current_time_ms();
	door_moves = check_exit_door(game, current_time);
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

bool	angle_between(double angle, double start, double end)
{
	angle = normalize_angle(angle);
	start = normalize_angle(start);
	end = normalize_angle(end);
	if (start < end)
		return (angle > start && angle < end);
	else
		return (angle > start || angle < end);
}

static void	update_doors_in_range(void)
{
	t_game	*g;
	t_point	player_pos;
	double	player_angle;
	char	**map;
	int		i;
	bool	loking_at_door_center;
	bool	close_enough;
	t_door	*door;
	bool	door_is_horizontale;
	t_point	door_center;
	bool	up;
	t_point	door_p1;
	t_point	door_p2;
	double	vertical_dist;
	double	p1_player_angle;
	double	p2_player_angle;
	bool	right;
	double	horizontal_dist;

	g = get_game();
	player_pos = g->player.p;
	player_angle = g->player.angle;
	map = g->data.map.arr;
	i = -2;
	while (++i < g->nb_of_doors)
	{
		if (i == -1)
			door = &g->exit;
		else
			door = &g->doors[i];
		door_is_horizontale = (map[(int)door->pos.y][(int)door->pos.x
				- 1] == '1');
		door_center = (t_point){.x = (door->pos.x + 0.5) * WALL_WIDTH,
			.y = (door->pos.y + 0.5) * WALL_WIDTH};
		if (door_is_horizontale)
		{
			up = (player_pos.y > door_center.y);
			if (player_pos.y == door_center.y)
			{
				door->in_range = false;
				return ;
			}
			door_p1 = (t_point){.x = (door->pos.x + 1.0 / 4.0) * WALL_WIDTH,
				.y = (door->pos.y + 0.5) * WALL_WIDTH};
			door_p2 = (t_point){.x = (door->pos.x + 3.0 / 4.0) * WALL_WIDTH,
				.y = (door->pos.y + 0.5) * WALL_WIDTH};
			vertical_dist = fabs(player_pos.y - door_center.y);
			close_enough = (vertical_dist < (1.5 * WALL_WIDTH))
				&& (door_center.x - WALL_WIDTH / 2 < player_pos.x
					&& player_pos.x < door_center.x + WALL_WIDTH / 2);
			p1_player_angle = normalize_angle(atan2(door_p1.y - player_pos.y,
						door_p1.x - player_pos.x));
			p2_player_angle = normalize_angle(atan2(door_p2.y - player_pos.y,
						door_p2.x - player_pos.x));
			if (up)
				loking_at_door_center = angle_between(player_angle,
						p1_player_angle, p2_player_angle);
			else
				loking_at_door_center = angle_between(player_angle,
						p2_player_angle, p1_player_angle);
		}
		else
		{
			right = (player_pos.x < door_center.x);
			door_p1 = (t_point){.x = (door->pos.x + 0.5) * WALL_WIDTH,
				.y = (door->pos.y + 1.0 / 3.0) * WALL_WIDTH};
			door_p2 = (t_point){.x = (door->pos.x + 0.5) * WALL_WIDTH,
				.y = (door->pos.y + 2.0 / 3.0) * WALL_WIDTH};
			horizontal_dist = fabs(player_pos.x - door_center.x);
			close_enough = (horizontal_dist < (1.5 * WALL_WIDTH))
				&& (door_center.y - WALL_WIDTH / 2 < player_pos.y
					&& player_pos.y < door_center.y + WALL_WIDTH / 2);
			p1_player_angle = normalize_angle(atan2(door_p1.y - player_pos.y,
						door_p1.x - player_pos.x));
			p2_player_angle = normalize_angle(atan2(door_p2.y - player_pos.y,
						door_p2.x - player_pos.x));
			if (right)
				loking_at_door_center = angle_between(player_angle,
						p1_player_angle, p2_player_angle);
			else
				loking_at_door_center = angle_between(player_angle,
						p2_player_angle, p1_player_angle);
			if (player_pos.x == door_center.x)
			{
				door->in_range = false;
				return ;
			}
		}
		door->in_range = (loking_at_door_center && close_enough);
	}
}

#define PORTAL_FRAME_DURATION_MS 10 // tweak speed
#define PORTAL_MAX_FRAMES 11 // 0..10

static void	update_portal_animation(t_game *g, long long current_time)
{
	// Only animate if the portal door is fully open
	if (g->exit.frame == 8)
	{
		if (current_time - g->exit.last_update >= PORTAL_FRAME_DURATION_MS)
		{
			g->portal_frame = (g->portal_frame + 1) % PORTAL_MAX_FRAMES;
			g->exit.last_update = current_time;
		}
	}
}

int	game_loop(t_game *game)
{
	static int	c;
	int			n;
	bool		scean_changed;
	bool		door_moving;
	long long	current_time;

	handle_exit(game);
	// if (handle_video("bonus/video/intro.mp4"))
	// 	return (1);
	door_moving = update_doors_states(game);
	scean_changed = game->player.moving || door_moving;
	handel_o_press(game);
	update_player(game);
	if (game->player.moving)
		update_doors_in_range();
	current_time = get_current_time_ms();
	update_portal_animation(game, current_time);
	// if (game->passed)
	// {
	// 	// play end video
	// 	// display win info
	// 	// exit gracefully
	// 	if (handle_video("/home/mbousset/Desktop/video/videos/short.mp4"))
	// 		return (1);
	// 	handle_close();
	// }
	if (scean_changed) // if player looking at open portal
	{
	//	printf("hello %d \n", c++);
		display_scean(game);
		draw_mini_map(game);
		//draw_timer(game, 1);
		mlx_put_image_to_window(game->mlx, game->win, game->display.img, 0, 0);
	}
	draw_timer(game, 0);
	return (1);
}

void	lunch_game_hooks(t_game *game)
{
	init_img_menu(game);
	draw_menu(game);
	mlx_do_key_autorepeatoff(game->mlx);
	mlx_hook(game->win, 2, 1L << 0, key_press, game);
	mlx_hook(game->win, 3, 1L << 1, key_release, game);
	mlx_hook(game->win, 17, 0, handle_close, NULL);
	mlx_hook(game->win, 6, 1L << 6, mouse_move, game);
	mlx_mouse_hook(game->win,mouse_click,game);
	//mlx_loop_hook(game->mlx, game_loop, game);
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
