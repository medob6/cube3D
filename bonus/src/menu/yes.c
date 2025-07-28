/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   yes.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omben-ch <omben-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 16:53:42 by omben-ch          #+#    #+#             */
/*   Updated: 2025/07/28 17:00:02 by omben-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void on_click_yes(t_game *game, int button)
{
    if (button == YES)
    {
        handle_close(game);
    }    
}

void on_hover_yes(t_game *game, int button)
{
    if (button == YES)
			game->buttons[YES].img = &game->graphic_menu[H_START_IMG];
	else
		game->buttons[YES].img = &game->graphic_menu[YES_IMG];
}

void create_yes_button(t_game *game,t_button *button)
{
    button->img = &game->graphic_menu[YES_IMG];
	button->start_x = 11*(game->win_w/ 20);
	button->start_y = (game->win_h/ 20)*10;
    button->width = game->win_w *2/ 20;
	button->height = game->win_h/ 20;
	button->end_x = button->start_x + button->width;
	button->end_y = button->start_y + button->height;
    button->on_click = on_click_yes;
    button->on_hover = on_hover_yes;
}
