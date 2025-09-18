/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_tools2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omben-ch <omben-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 16:14:14 by omben-ch          #+#    #+#             */
/*   Updated: 2025/09/16 16:14:15 by omben-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_bs.h"

void	get_exit_door_corners(t_door *door, char **map, t_point *p1,
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

bool	sweep_fov_for_door(t_game *g, double player_angle, double p1_angle,
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
