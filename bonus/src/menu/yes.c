/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   yes.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omben-ch <omben-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 16:53:42 by omben-ch          #+#    #+#             */
/*   Updated: 2025/09/13 18:33:09 by omben-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_bs.h"

void	on_click_yes(t_game *game, int button)
{
	if (game->end_start_menu != EXIT)
		return ;
	if (button == YES)
	{
		handle_close();
	}
}

void	on_hover_yes(t_game *game, int button)
{
	if (game->end_start_menu != EXIT)
		return ;
	if (button == YES)
		game->buttons[YES].img = &game->graphic_menu[H_YES_IMG];
	else
		game->buttons[YES].img = &game->graphic_menu[YES_IMG];
}

void	create_yes_button(t_game *game, t_button *button)
{
	button->img = &game->graphic_menu[YES_IMG];
	button->start_x = 7 * (game->win_w / 20);
	button->start_y = 10.8 * (game->win_h / 20);
	button->end_x = 8 * (game->win_w / 20);
	button->end_y = 12.2 * (game->win_h / 20);
	button->width = button->end_x - button->start_x;
	button->height = button->end_y - button->start_y;
	button->on_click = on_click_yes;
	button->on_hover = on_hover_yes;
}
