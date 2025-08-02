/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   yes.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omben-ch <omben-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 16:53:42 by omben-ch          #+#    #+#             */
/*   Updated: 2025/08/02 09:50:21 by omben-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void on_click_yes(t_game *game, int button)
{
    if (game->end_start_menu != EXIT)
        return;
    if (button == YES)
    {
        handle_close(game);
    }    
}

void on_hover_yes(t_game *game, int button)
{
    if (game->end_start_menu != EXIT)
        return;
    if (button == YES)
			game->buttons[YES].img = &game->graphic_menu[H_YES_IMG];
	else
		game->buttons[YES].img = &game->graphic_menu[YES_IMG];
}

void create_yes_button(t_game *game,t_button *button)
{
    
    button->img = &game->graphic_menu[YES_IMG];
	button->start_x = 7.35 * (game->win_w / 21);
	button->start_y = 11.2 * (game->win_h/ 21);
    button->width = game->win_w * 0.98 / 21;
	button->height = game->win_h * 1.5 / 21;
	button->end_x = button->start_x + button->width;
	button->end_y = button->start_y + button->height;
    button->on_click = on_click_yes;
    button->on_hover = on_hover_yes;

}
