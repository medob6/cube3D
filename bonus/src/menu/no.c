/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   no.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omben-ch <omben-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 16:53:53 by omben-ch          #+#    #+#             */
/*   Updated: 2025/08/22 17:06:40 by omben-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_bs.h"

void on_click_no(t_game *game, int button)
{
    if (game->end_start_menu != EXIT)
        return;
    if (button == NO)
    {
		game->end_start_menu = START;
        game->buttons[YES].img = &game->graphic_menu[YES_IMG];
		game->buttons[NO].img = &game->graphic_menu[NO_IMG];
    }
}

void on_hover_no(t_game *game, int button)
{
    if (game->end_start_menu != EXIT)
        return;
    if (button == NO)
			game->buttons[NO].img = &game->graphic_menu[H_NO_IMG];
	else
		game->buttons[NO].img = &game->graphic_menu[NO_IMG];
}

void create_no_button(t_game *game,t_button *button)
{
    button->img = &game->graphic_menu[NO_IMG];
	button->start_x = 11.87 * (game->win_w / 21);
	button->start_y = 11.2 * (game->win_h/ 21);
    button->width = game->win_w * 0.98 / 21;
	button->height = game->win_h * 1.5 / 21;
	button->end_x = button->start_x + button->width;
	button->end_y = button->start_y + button->height;
    button->on_click = on_click_no;
    button->on_hover = on_hover_no;
}
