/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_tools1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omben-ch <omben-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 16:14:12 by omben-ch          #+#    #+#             */
/*   Updated: 2025/09/16 16:14:13 by omben-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_bs.h"

void	start_opening_door(t_door *door)
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

void	update_opening_door(t_door *door, long long current_time)
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

void	update_closing_door(t_door *door, long long current_time)
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

bool	is_exit_door_horizontal(t_door *door, char **map)
{
	return (map[(int)door->pos.y][(int)door->pos.x - 1] == '1'
		&& map[(int)door->pos.y][(int)door->pos.x + 1] == '1');
}
