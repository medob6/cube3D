/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   control.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omben-ch <omben-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 15:19:53 by omben-ch          #+#    #+#             */
/*   Updated: 2025/07/28 16:29:00 by omben-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void on_click_control(t_game *game, int button)
{
	if (button == CONTROL)
	{
		game->end_start_menu = 1;
		put_bg(game, &game->graphic_menu[CONTROL_PAGE_IMG]);
		mlx_put_image_to_window(game->mlx, game->win, game->display.img, 0, 0);
	}	
}

void on_hover_control(t_game *game, int button)
{
    if (button == CONTROL)
			game->buttons[CONTROL].img = &game->graphic_menu[H_CONTROL_IMG];
	else
		game->buttons[CONTROL].img = &game->graphic_menu[CONTROL_IMG];
}

void create_control_button(t_game *game,t_button *button)
{
    button->img = &game->graphic_menu[CONTROL_IMG];
	button->start_x = 5*(game->win_w/ 8);
	button->start_y = (game->win_h/ 8)*4;
	button->end_x = game->win_w - ((game->win_w/ 8));
	button->end_y = (game->win_h / 8) * 5;
	button->width = button->end_x - button->start_x;
	button->height = button->end_y - button->start_y;
    button->on_click = on_click_control;
    button->on_hover = on_hover_control;
}
