/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_event.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omben-ch <omben-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/31 13:10:57 by omben-ch          #+#    #+#             */
/*   Updated: 2025/09/13 18:35:41 by omben-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_bs.h"

int	check_button(t_game *game, int x, int y)
{
	int	i;

	i = -1;
	while (++i < NB_BUTTON)
	{
		if ((x >= game->buttons[i].start_x && x <= game->buttons[i].end_x)
			&& (y >= game->buttons[i].start_y && y <= game->buttons[i].end_y))
			return (i);
	}
	return (-1);
}

int	mouse_move(int x, int y, t_game *game)
{
	int	button;
	int	i;

	i = -1;
	if (game->end_start_menu == IN_PLY_L_VID
		|| game->end_start_menu == IN_PLY_W_VID
		|| game->end_start_menu == IN_PLY_I_VID)
		return (1);
	if (game->end_start_menu == IN_GAME)
	{
		mouse_move_handler(x, y, game);
		return (0);
	}
	button = check_button(game, x, y);
	while (++i < NB_BUTTON)
		game->buttons[i].on_hover(game, button);
	draw_menu(game);
	return (0);
}

int	mouse_click(int code, int x, int y, t_game *game)
{
	int	button;
	int	i;

	if (game->end_start_menu == IN_PLY_L_VID
		|| game->end_start_menu == IN_PLY_W_VID
		|| game->end_start_menu == IN_PLY_I_VID)
		return (1);
	i = -1;
	button = check_button(game, x, y);
	if (code == 1 && game->end_start_menu == IN_GAME)
	{
		game->keys[9].press = true;
		handel_o_press(game);
		game->keys[9].press = false;
	}
	if (code == 1)
	{
		while (++i < NB_BUTTON)
			game->buttons[i].on_click(game, button);
		draw_menu(game);
	}
	return (0);
}
