/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_event.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omben-ch <omben-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 13:10:57 by omben-ch          #+#    #+#             */
/*   Updated: 2025/09/09 14:13:41 by omben-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_bs.h"

int	mouse_move(int x, int y, t_game *game)
{
	int button;
	int i;

	i = -1;
	if (game->end_start_menu == -1)
	{
		mouse_move_handler(x, y, game);
		return 0;
	}
	button = check_button(game,x,y);
	while (++i < NB_BUTTON)
		game->buttons[i].on_hover(game,button);
	draw_menu(game);
	return 0;
}

int mouse_click(int code, int x,int y ,t_game *game)
{
	int button;
	int i;

	i = -1;
	button = check_button(game,x,y);
	if (code == 1)
	{
		while (++i < NB_BUTTON)
			game->buttons[i].on_click(game, button);
		draw_menu(game);
	}
	return (0);
}
