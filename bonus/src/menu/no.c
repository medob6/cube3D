/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   no.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omben-ch <omben-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 16:53:53 by omben-ch          #+#    #+#             */
/*   Updated: 2025/07/28 16:59:55 by omben-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void on_click_no(t_game *game, int button)
{
    if (button == NO)
    {
        draw_menu(game);
		game->end_start_menu = 0;
    }    
}

void on_hover_no(t_game *game, int button)
{
    if (button == NO)
			game->buttons[NO].img = &game->graphic_menu[H_START_IMG];
	else
		game->buttons[NO].img = &game->graphic_menu[NO_IMG];
}

void create_no_button(t_game *game,t_button *button)
{
    button->img = &game->graphic_menu[NO_IMG];
	button->start_x = 8*(game->win_w/ 20);
	button->start_y = (game->win_h/ 20)*10;
    button->width = game->win_w *2/ 20;
	button->height = game->win_h/ 20;
	button->end_x = button->start_x + button->width;
	button->end_y = button->start_y + button->height;
    button->on_click = on_click_no;
    button->on_hover = on_hover_no;
}
