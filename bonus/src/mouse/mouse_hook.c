/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_hook.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omben-ch <omben-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 13:22:27 by omben-ch          #+#    #+#             */
/*   Updated: 2025/09/10 11:37:12 by omben-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_bs.h"

int mouse_move_handler(int x, int y, t_game *game)
{
	static int prev_x = -1;
	static int prev_y = -1;
	int tmp;

	if (prev_x != -1)
	{
		tmp = x - prev_x;
		if (abs(tmp) > 2)
		{
            game->player.angle  += tmp * 0.01;
		}
	}
	if (prev_y != -1)
	{
		tmp = y - prev_y;
		if (abs(tmp) > 2)
		{
            game->player.p.z -= tmp ;
		}
	}
	prev_x = x;
	prev_y = y;
    game->player.moving = true;
    return (0);
}
