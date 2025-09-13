/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   return.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omben-ch <omben-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/01 15:50:46 by omben-ch          #+#    #+#             */
/*   Updated: 2025/09/13 18:32:52 by omben-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_bs.h"

void	on_click_return(t_game *game, int button)
{
	if (game->end_start_menu != CONTROL)
		return ;
	if (button == RETURN)
	{
		game->end_start_menu = START;
		game->buttons[RETURN].img = &game->graphic_menu[RETURN_IMG];
	}
}

void	on_hover_return(t_game *game, int button)
{
	if (game->end_start_menu != CONTROL)
		return ;
	if (button == RETURN)
		game->buttons[RETURN].img = &game->graphic_menu[H_RETURN_IMG];
	else
		game->buttons[RETURN].img = &game->graphic_menu[RETURN_IMG];
}

void	create_return_button(t_game *game, t_button *button)
{
	button->img = &game->graphic_menu[RETURN_IMG];
	button->start_x = 12 * (game->win_w / 13);
	button->start_y = 0;
	button->end_x = game->win_w;
	button->end_y = (game->win_h / 13);
	button->width = button->end_x - button->start_x;
	button->height = button->end_y - button->start_y;
	button->on_click = on_click_return ;
	button->on_hover = on_hover_return ;
}
