/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_res.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omben-ch <omben-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 15:58:30 by omben-ch          #+#    #+#             */
/*   Updated: 2025/08/05 15:58:39 by omben-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void init_min_part(t_game *game)
{
    game->timer[0].img = &game->graphic_menu[NUMBERS_IMG];
	game->timer[0].start_x = 0;
	game->timer[0].start_y = 0.1 * (game->win_h / 30);
	game->timer[0].end_x = game->win_w / 35;
	game->timer[0].end_y = (game->win_h / 30);
	game->timer[0].width = game->timer[0].end_x - game->timer[0].start_x;
	game->timer[0].height = game->timer[0].end_y - game->timer[0].start_y;
    game->timer[1].img = &game->graphic_menu[NUMBERS_IMG];
	game->timer[1].start_x = game->win_w / 35;
	game->timer[1].start_y = 0.1 * (game->win_h / 30);
	game->timer[1].end_x = game->win_w * 2/ 35;
	game->timer[1].end_y = (game->win_h / 30);
	game->timer[1].width = game->timer[1].end_x - game->timer[1].start_x;
	game->timer[1].height = game->timer[1].end_y - game->timer[1].start_y;
}

void init_point_part(t_game *game)
{
    game->timer[2].img = &game->graphic_menu[NUMBERS_IMG];
	game->timer[2].start_x = game->win_w *2/ 35;
	game->timer[2].start_y = 0.1 * (game->win_h / 30);
	game->timer[2].end_x = game->win_w * 3/ 35;
	game->timer[2].end_y = (game->win_h / 30);
	game->timer[2].width = game->timer[2].end_x - game->timer[2].start_x;
	game->timer[2].height = game->timer[2].end_y - game->timer[2].start_y;
}

void init_sec_part(t_game *game)
{
    game->timer[3].img = &game->graphic_menu[NUMBERS_IMG];
	game->timer[3].start_x = game->win_w * 3/ 35;
	game->timer[3].start_y = 0.1 * (game->win_h / 30);
	game->timer[3].end_x = game->win_w * 4/ 35;
	game->timer[3].end_y = (game->win_h / 30);
	game->timer[3].width = game->timer[3].end_x - game->timer[3].start_x;
	game->timer[3].height = game->timer[3].end_y - game->timer[3].start_y;
    game->timer[4].img = &game->graphic_menu[NUMBERS_IMG];
	game->timer[4].start_x = game->win_w * 4/ 35;
	game->timer[4].start_y = 0.1 * (game->win_h / 30);
	game->timer[4].end_x = game->win_w * 5/ 35;
	game->timer[4].end_y = (game->win_h / 30);
	game->timer[4].width = game->timer[4].end_x - game->timer[4].start_x;
	game->timer[4].height = game->timer[4].end_y - game->timer[4].start_y;
}

void init_timer_pic(t_game *game)
{
    init_min_part(game);
    init_point_part(game);
    init_sec_part(game);
}
