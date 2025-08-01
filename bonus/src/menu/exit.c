/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omben-ch <omben-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 15:25:13 by omben-ch          #+#    #+#             */
/*   Updated: 2025/08/01 16:35:07 by omben-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void on_click_exit(t_game *game, int button)
{
	if (game->end_start_menu != START)
        return;
	if (button == EXIT)
	{
		game->end_start_menu = EXIT;
		game->buttons[EXIT].img = &game->graphic_menu[EXIT_IMG];
		put_bg(game, &game->graphic_menu[EXIT_PAGE_IMG]);
		put_imag(game,&game->buttons[YES]);
		put_imag(game,&game->buttons[NO]);
		mlx_put_image_to_window(game->mlx, game->win, game->display.img, 0, 0);
	}
}

void on_hover_exit(t_game *game, int button)
{
	if (game->end_start_menu != START)
        return;
    if (button == EXIT)
			game->buttons[EXIT].img = &game->graphic_menu[H_EXIT_IMG];
	else
		game->buttons[EXIT].img = &game->graphic_menu[EXIT_IMG];
	// put_bg(game, &game->graphic_menu[BG_IMG]);
	// put_imag(game,&game->buttons[EXIT]);
	// mlx_put_image_to_window(game->mlx, game->win, game->display.img, 0, 0);	
}

void create_exit_button(t_game *game,t_button *button)
{
    button->img = &game->graphic_menu[EXIT_IMG];
	button->start_x = 5*(game->win_w/ 8);
	button->start_y = (game->win_h/ 8)*5;
	button->end_x = game->win_w - ((game->win_w/ 8));
	button->end_y = (game->win_h / 8) * 6;
	button->width = button->end_x - button->start_x;
	button->height = button->end_y - button->start_y;
    button->on_click = on_click_exit;
    button->on_hover = on_hover_exit;
}
