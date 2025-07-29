/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   no.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omben-ch <omben-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 16:53:53 by omben-ch          #+#    #+#             */
/*   Updated: 2025/07/29 11:22:41 by omben-ch         ###   ########.fr       */
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
	button->start_x = ((5 + 7.5) / 2.0 + 7.5)/ 2* (game->win_w/ 20);
	button->start_y = 10.5 * (game->win_h/ 20);
    button->width = game->win_w *1/ 20;
	button->height = button->width * button->img->h/ button->img->w;
	button->end_x = button->start_x + button->width;
	button->end_y = button->start_y + button->height;
    button->on_click = on_click_no;
    button->on_hover = on_hover_no;
}
