/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omben-ch <omben-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 14:39:47 by omben-ch          #+#    #+#             */
/*   Updated: 2025/09/13 18:32:58 by omben-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_bs.h"

void	on_click_start(t_game *game, int button)
{
	if (game->end_start_menu != START)
		return ;
	if (button == START)
	{
		game->end_start_menu = IN_GAME;
		game->buttons[START].img = &game->graphic_menu[START_IMG];
	}
}

void	on_hover_start(t_game *game, int button)
{
	if (game->end_start_menu != START)
		return ;
	if (button == START)
		game->buttons[START].img = &game->graphic_menu[H_START_IMG];
	else
		game->buttons[START].img = &game->graphic_menu[START_IMG];
}

void	create_start_button(t_game *game, t_button *button)
{
	button->img = &game->graphic_menu[START_IMG];
	button->start_x = 5 * (game->win_w / 8);
	button->start_y = (game->win_h / 8) * 3;
	button->width = game->win_w * 2 / 8;
	button->height = game->win_h / 8;
	button->end_x = button->start_x + button->width;
	button->end_y = button->start_y + button->height;
	button->on_click = on_click_start;
	button->on_hover = on_hover_start;
}
