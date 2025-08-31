/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_res.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omben-ch <omben-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 15:58:30 by omben-ch          #+#    #+#             */
/*   Updated: 2025/08/22 17:06:40 by omben-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_bs.h"

void init_timer_bg_part(t_game *game)
{
    game->timer[TIMER_BG].img = &game->graphic_menu[TIMER_BG_IMG];
	game->timer[TIMER_BG].start_x = 0;
	game->timer[TIMER_BG].start_y = 0;
	game->timer[TIMER_BG].end_x = game->win_w * 6.8 / 30;
	game->timer[TIMER_BG].end_y = (game->win_h * 2 / 15);
	game->timer[TIMER_BG].width = game->timer[TIMER_BG].end_x - game->timer[TIMER_BG].start_x;
	game->timer[TIMER_BG].height = game->timer[TIMER_BG].end_y - game->timer[TIMER_BG].start_y;
}
void init_min_part(t_game *game)
{
    game->timer[FP_MIN].img = &game->graphic_menu[NUMBERS_IMG];
	game->timer[FP_MIN].start_x = 1.5*game->win_w / 35;
	game->timer[FP_MIN].start_y = 2 * (game->win_h / 30);
	game->timer[FP_MIN].end_x = 2.5*game->win_w / 35;
	game->timer[FP_MIN].end_y = 3*(game->win_h / 30);
	game->timer[FP_MIN].width = game->timer[FP_MIN].end_x - game->timer[FP_MIN].start_x;
	game->timer[FP_MIN].height = game->timer[FP_MIN].end_y - game->timer[FP_MIN].start_y;
	game->timer[FP_MIN].min = 0;
    
	game->timer[SP_MIN].img = &game->graphic_menu[NUMBERS_IMG];
	game->timer[SP_MIN].start_x = 2.5 * game->win_w / 35;
	game->timer[SP_MIN].start_y = 2 * (game->win_h / 30);
	game->timer[SP_MIN].end_x = 3.5*game->win_w / 35;
	game->timer[SP_MIN].end_y = 3*(game->win_h / 30);
	game->timer[SP_MIN].width = game->timer[SP_MIN].end_x - game->timer[SP_MIN].start_x;
	game->timer[SP_MIN].height = game->timer[SP_MIN].end_y - game->timer[SP_MIN].start_y;
	game->timer[SP_MIN].min = 0;
}

void init_point_part(t_game *game)
{
    game->timer[POINT].img = &game->graphic_menu[POINT_IMG];
	game->timer[POINT].start_x = 3.5*game->win_w / 35;
	game->timer[POINT].start_y = 2 * (game->win_h / 30);
	game->timer[POINT].end_x = 4.5*game->win_w / 35;
	game->timer[POINT].end_y = 3*(game->win_h / 30);
	game->timer[POINT].width = game->timer[POINT].end_x - game->timer[POINT].start_x;
	game->timer[POINT].height = game->timer[POINT].end_y - game->timer[POINT].start_y;
}

void init_sec_part(t_game *game)
{
    game->timer[FP_SEC].img = &game->graphic_menu[NUMBERS_IMG];
	game->timer[FP_SEC].start_x = 4.5*game->win_w / 35;
	game->timer[FP_SEC].start_y = 2 * (game->win_h / 30);
	game->timer[FP_SEC].end_x = 5.5*game->win_w / 35;
	game->timer[FP_SEC].end_y = 3*(game->win_h / 30);
	game->timer[FP_SEC].width = game->timer[FP_SEC].end_x - game->timer[FP_SEC].start_x;
	game->timer[FP_SEC].height = game->timer[FP_SEC].end_y - game->timer[FP_SEC].start_y;
	game->timer[FP_SEC].sec = 0;

    game->timer[SP_SEC].img = &game->graphic_menu[NUMBERS_IMG];
	game->timer[SP_SEC].start_x = 5.5*game->win_w / 35;
	game->timer[SP_SEC].start_y = 2 * (game->win_h / 30);
	game->timer[SP_SEC].end_x = 6.5*game->win_w / 35;
	game->timer[SP_SEC].end_y = 3*(game->win_h / 30);
	game->timer[SP_SEC].width = game->timer[SP_SEC].end_x - game->timer[SP_SEC].start_x;
	game->timer[SP_SEC].height = game->timer[SP_SEC].end_y - game->timer[SP_SEC].start_y;
	game->timer[SP_SEC].sec = 0;
}

void init_timer_pic(t_game *game)
{
	init_timer_bg_part(game);
    init_min_part(game);
    init_point_part(game);
    init_sec_part(game);
}
