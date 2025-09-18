/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_tools3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbousset <mbousset@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 16:14:17 by omben-ch          #+#    #+#             */
/*   Updated: 2025/09/18 09:10:26 by mbousset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_bs.h"

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

bool	is_horizontal_door(t_door *door, char **map)
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

bool	check_horizontal_door(t_door *door, t_point p_pos,
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
