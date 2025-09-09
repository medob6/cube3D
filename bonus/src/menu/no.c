/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   no.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omben-ch <omben-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 16:53:53 by omben-ch          #+#    #+#             */
/*   Updated: 2025/09/04 11:02:37 by omben-ch         ###   ########.fr       */
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
	button->start_x = 11.3 * (game->win_w / 20);
	button->start_y = 10.8 * (game->win_h / 20);
    button->end_x = 12.3 * (game->win_w / 20);
	button->end_y = 12.2 * (game->win_h / 20);
	button->width = button->end_x - button->start_x;
	button->height = button->end_y - button->start_y;
    button->on_click = on_click_no;
    button->on_hover = on_hover_no;
}
