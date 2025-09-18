/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_tools4.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbousset <mbousset@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 16:14:20 by omben-ch          #+#    #+#             */
/*   Updated: 2025/09/18 09:10:31 by mbousset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_bs.h"
#include "raycaster_bs.h"

bool	check_vertical_door(t_door *door, t_point p_pos,
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

void	update_single_door_in_range(t_door *door, t_point player_pos,
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

void	update_doors_in_range(void)
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

void	update_portal_animation(t_game *g, long long current_time)
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
