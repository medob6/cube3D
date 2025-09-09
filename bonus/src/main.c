/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omben-ch <omben-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 09:38:33 by omben-ch          #+#    #+#             */
/*   Updated: 2025/09/09 11:52:02 by omben-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycaster_bs.h"
// #include "video_bs.h"

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
	return (((long long)(tv.tv_sec) * 1000) + (tv.tv_usec / 1000));
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
// 	video_result = play_video(path);
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

	last_fram = get_game()->graphics[DOOR].frames - 1;
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
	int		n;

	n = -1;
	if (!get_key(KEY_O, game)->press)
		return ;
	if (game->exit.in_range && door_is_closed(game->exit))
		start_closing_door(&game->exit);
	else if (game->exit.in_range)
		start_opening_door(&game->exit);
	while (++n < game->nb_of_doors)
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
		if (door->frame < get_game()->graphics[DOOR].frames - 1)
		{
			door->frame++;
			door->last_update = current_time;
		}
		else
			door->opening = false;
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
			door->closing = false;
	}
}

static bool	is_exit_door_horizontal(t_door *door, char **map)
{
	return (map[(int)door->pos.y][(int)door->pos.x - 1] == '1'
		&& map[(int)door->pos.y][(int)door->pos.x + 1] == '1');
}

static void	get_exit_door_corners(t_door *door, char **map, t_point *p1,
		t_point *p2)
{
	if (is_exit_door_horizontal(door, map))
	{
		*p1 = (t_point){.x = (door->pos.x) * WALL_WIDTH, .y = (door->pos.y
				+ 0.5) * WALL_WIDTH};
		*p2 = (t_point){.x = (door->pos.x + 1) * WALL_WIDTH, .y = (door->pos.y
				+ 0.5) * WALL_WIDTH};
	}
	else
	{
		*p1 = (t_point){.x = (door->pos.x + 0.5) * WALL_WIDTH,
			.y = (door->pos.y) * WALL_WIDTH};
		*p2 = (t_point){.x = (door->pos.x + 0.5) * WALL_WIDTH, .y = (door->pos.y
				+ 1) * WALL_WIDTH};
	}
}

static bool	sweep_fov_for_door(t_game *g, double player_angle, double p1_angle,
		double p2_angle)
{
	double	angle_step;
	double	angle;
	int		x;

	angle_step = FOV_ANGLE / (double)g->win_w;
	angle = player_angle - FOV_ANGLE / 2.0;
	x = -1;
	while (++x < g->win_w)
	{
		angle = normalize_angle(angle + angle_step);
		if (angle_between(angle, p1_angle, p2_angle))
			return (true);
	}
	return (false);
}

bool	looking_at_open_portal(t_game *g)
{
	t_point	player_pos;
	t_door	*door;
	t_point	door_p1;
	t_point	door_p2;
	t_pair	palyer_ang_bounds;

	player_pos = g->player.p;
	door = &g->exit;
	get_exit_door_corners(door, g->data.map.arr, &door_p1, &door_p2);
	palyer_ang_bounds.x = normalize_angle(atan2(door_p1.y - player_pos.y,
				door_p1.x - player_pos.x));
	palyer_ang_bounds.y = normalize_angle(atan2(door_p2.y - player_pos.y,
				door_p2.x - player_pos.x));
	return (sweep_fov_for_door(g, g->player.angle, palyer_ang_bounds.x,
			palyer_ang_bounds.y));
}

bool	check_exit_door(t_game *g, long long current_time)
{
	bool	moved;

	moved = false;
	if (g->exit.opening)
	{
		moved = true;
		update_opening_door(&g->exit, current_time);
	}
	else if (g->exit.closing)
	{
		moved = true;
		update_closing_door(&g->exit, current_time);
	}
	if (g->exit.frame == g->graphics[DOOR].frames - 1)
	{
		if (looking_at_open_portal(g))
			return (true);
	}
	return (moved);
}

bool	update_doors_states(t_game *game)
{
	bool		door_moves;
	long long	current_time;
	t_door		*door;
	int			n;

	n = -1;
	door_moves = false;
	current_time = get_current_time_ms();
	door_moves = check_exit_door(game, current_time);
	while (++n < game->nb_of_doors)
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

	n = 0;
	while (n < game->nb_of_doors)
	{
		game->doors[n].in_range = false;
		n++;
	}
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

static bool	is_horizontal_door(t_door *door, char **map)
{
	return (map[(int)door->pos.y][(int)door->pos.x - 1] == '1');
}

bool	is_door_close_enough(t_point p_pos, t_point door_center,
		bool horizontal)
{
	double	vertical_dist;
	double	horiz_dist;

	if (horizontal)
	{
		vertical_dist = fabs(p_pos.y - door_center.y);
		return ((vertical_dist < (1.5 * WALL_WIDTH)) && (door_center.x
				- WALL_WIDTH / 2 < p_pos.x && p_pos.x < door_center.x
				+ WALL_WIDTH / 2));
	}
	else
	{
		horiz_dist = fabs(p_pos.x - door_center.x);
		return ((horiz_dist < (1.5 * WALL_WIDTH)) && (door_center.y - WALL_WIDTH
				/ 2 < p_pos.y && p_pos.y < door_center.y + WALL_WIDTH / 2));
	}
}

static bool	check_horizontal_door(t_door *door, t_point p_pos,
		double player_angle, t_point door_center)
{
	t_point	door_p1;
	t_point	door_p2;
	t_pair	palyer_ang_bounds;
	bool	up;
	bool	close_enough;

	if (p_pos.y == door_center.y)
		return (false);
	up = (p_pos.y > door_center.y);
	door_p1 = (t_point){.x = (door->pos.x + 0.25) * WALL_WIDTH,
		.y = (door->pos.y + 0.5) * WALL_WIDTH};
	door_p2 = (t_point){.x = (door->pos.x + 0.75) * WALL_WIDTH,
		.y = (door->pos.y + 0.5) * WALL_WIDTH};
	close_enough = is_door_close_enough(p_pos, door_center, true);
	palyer_ang_bounds.x = normalize_angle(atan2(door_p1.y - p_pos.y, door_p1.x
				- p_pos.x));
	palyer_ang_bounds.y = normalize_angle(atan2(door_p2.y - p_pos.y, door_p2.x
				- p_pos.x));
	if (up)
		return (close_enough && angle_between(player_angle, palyer_ang_bounds.x,
				palyer_ang_bounds.y));
	return (close_enough && angle_between(player_angle, palyer_ang_bounds.y,
			palyer_ang_bounds.x));
}

bool	is_close_enough(void)
{
}

static bool	check_vertical_door(t_door *door, t_point p_pos,
		double player_angle, t_point door_center)
{
	t_point	door_p1;
	t_point	door_p2;
	t_pair	palyer_ang_bounds;
	bool	right;
	bool	close_enough;

	if (p_pos.x == door_center.x)
		return (false);
	right = (p_pos.x < door_center.x);
	door_p1 = (t_point){.x = (door->pos.x + 0.5) * WALL_WIDTH, .y = (door->pos.y
			+ 1.0 / 3.0) * WALL_WIDTH};
	door_p2 = (t_point){.x = (door->pos.x + 0.5) * WALL_WIDTH, .y = (door->pos.y
			+ 2.0 / 3.0) * WALL_WIDTH};
	close_enough = is_door_close_enough(p_pos, door_center, false);
	palyer_ang_bounds.x = normalize_angle(atan2(door_p1.y - p_pos.y, door_p1.x
				- p_pos.x));
	palyer_ang_bounds.y = normalize_angle(atan2(door_p2.y - p_pos.y, door_p2.x
				- p_pos.x));
	if (right)
		return (close_enough && angle_between(player_angle, palyer_ang_bounds.x,
				palyer_ang_bounds.y));
	return (close_enough && angle_between(player_angle, palyer_ang_bounds.y,
			palyer_ang_bounds.x));
}

static void	update_single_door_in_range(t_door *door, t_point player_pos,
		double player_angle, char **map)
{
	t_point	door_center;

	door_center = (t_point){.x = (door->pos.x + 0.5) * WALL_WIDTH,
		.y = (door->pos.y + 0.5) * WALL_WIDTH};
	if (is_horizontal_door(door, map))
		door->in_range = check_horizontal_door(door, player_pos, player_angle,
				door_center);
	else
		door->in_range = check_vertical_door(door, player_pos, player_angle,
				door_center);
}

static void	update_doors_in_range(void)
{
	t_point	player_pos;
	double	player_angle;
	char	**map;
	int		i;
	t_door	*door;

	player_pos = get_game()->player.p;
	player_angle = get_game()->player.angle;
	map = get_game()->data.map.arr;
	i = -2;
	while (++i < get_game()->nb_of_doors)
	{
		if (i == -1)
			door = &get_game()->exit;
		else
			door = &get_game()->doors[i];
		update_single_door_in_range(door, player_pos, player_angle, map);
	}
}

static void	update_portal_animation(t_game *g, long long current_time)
{
	if (g->exit.frame == get_game()->graphics[DOOR].frames - 1)
	{
		if (current_time - g->exit.last_update >= PORTAL_FRAME_DURATION_MS)
		{
			g->portal_frame = (g->portal_frame + 1)
				% g->graphics[PORTAL].frames;
			g->exit.last_update = current_time;
		}
	}
}

void	lunch_cube(t_game *game)
{
	display_scean(game);
	draw_mini_map(game);
	mlx_put_image_to_window(game->mlx, game->win, game->display.img, 0, 0);
}

int	game_loop(t_game *game)
{
	bool	scean_changed;
	bool	door_moving;

	handle_exit(game);
	// set_play_speed(150); // example: 1.5x audio speed
	// play_video("video/intro.mp4");
	door_moving = update_doors_states(game);
	scean_changed = game->player.moving || door_moving;
	handel_o_press(game);
	update_player(game);
	if (game->player.moving)
		update_doors_in_range();
	update_portal_animation(game, get_current_time_ms());
	if (game->passed)
	{
		// set_play_speed(150);
		//play_video("video/short.mp4");
		handle_close();
	}
	if (scean_changed)
		lunch_cube(game);
	// if (should_clean_vlc())
	// 	clear_vlc();
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
