/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_res.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omben-ch <omben-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 15:58:30 by omben-ch          #+#    #+#             */
/*   Updated: 2025/08/05 18:57:57 by omben-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void init_timer_bg_part(t_game *game)
{
    game->timer[TIMER_BG].img = &game->graphic_menu[TIMER_BG_IMG];
	game->timer[TIMER_BG].start_x = 0;
	game->timer[TIMER_BG].start_y = 0;
	game->timer[TIMER_BG].end_x = game->win_w * 7 / 35;
	game->timer[TIMER_BG].end_y = (game->win_h * 2 / 30);
	game->timer[TIMER_BG].width = game->timer[TIMER_BG].end_x - game->timer[TIMER_BG].start_x;
	game->timer[TIMER_BG].height = game->timer[TIMER_BG].end_y - game->timer[TIMER_BG].start_y;
}
void init_min_part(t_game *game)
{
    game->timer[FP_MIN].img = &game->graphic_menu[NUMBERS_IMG];
	game->timer[FP_MIN].start_x = 0;
	game->timer[FP_MIN].start_y = 0.1 * (game->win_h / 30);
	game->timer[FP_MIN].end_x = game->win_w / 35;
	game->timer[FP_MIN].end_y = (game->win_h / 30);
	game->timer[FP_MIN].width = game->timer[FP_MIN].end_x - game->timer[FP_MIN].start_x;
	game->timer[FP_MIN].height = game->timer[FP_MIN].end_y - game->timer[FP_MIN].start_y;
	game->timer[FP_MIN].min = 2;
    
	game->timer[SP_MIN].img = &game->graphic_menu[NUMBERS_IMG];
	game->timer[SP_MIN].start_x = game->win_w / 35;
	game->timer[SP_MIN].start_y = 0.1 * (game->win_h / 30);
	game->timer[SP_MIN].end_x = game->win_w * 2/ 35;
	game->timer[SP_MIN].end_y = (game->win_h / 30);
	game->timer[SP_MIN].width = game->timer[SP_MIN].end_x - game->timer[SP_MIN].start_x;
	game->timer[SP_MIN].height = game->timer[SP_MIN].end_y - game->timer[SP_MIN].start_y;
	game->timer[SP_MIN].min = 4;
}

void init_point_part(t_game *game)
{
    game->timer[POINT].img = &game->graphic_menu[POINT_IMG];
	game->timer[POINT].start_x = game->win_w *2/ 35;
	game->timer[POINT].start_y = 0.1 * (game->win_h / 30);
	game->timer[POINT].end_x = game->win_w * 3/ 35;
	game->timer[POINT].end_y = (game->win_h / 30);
	game->timer[POINT].width = game->timer[POINT].end_x - game->timer[POINT].start_x;
	game->timer[POINT].height = game->timer[POINT].end_y - game->timer[POINT].start_y;
}

void init_sec_part(t_game *game)
{
    game->timer[FP_SEC].img = &game->graphic_menu[NUMBERS_IMG];
	game->timer[FP_SEC].start_x = game->win_w * 3/ 35;
	game->timer[FP_SEC].start_y = 0.1 * (game->win_h / 30);
	game->timer[FP_SEC].end_x = game->win_w * 4/ 35;
	game->timer[FP_SEC].end_y = (game->win_h / 30);
	game->timer[FP_SEC].width = game->timer[FP_SEC].end_x - game->timer[FP_SEC].start_x;
	game->timer[FP_SEC].height = game->timer[FP_SEC].end_y - game->timer[FP_SEC].start_y;
	game->timer[FP_SEC].sec = 9;

    game->timer[SP_SEC].img = &game->graphic_menu[NUMBERS_IMG];
	game->timer[SP_SEC].start_x = game->win_w * 4/ 35;
	game->timer[SP_SEC].start_y = 0.1 * (game->win_h / 30);
	game->timer[SP_SEC].end_x = game->win_w * 5/ 35;
	game->timer[SP_SEC].end_y = (game->win_h / 30);
	game->timer[SP_SEC].width = game->timer[SP_SEC].end_x - game->timer[SP_SEC].start_x;
	game->timer[SP_SEC].height = game->timer[SP_SEC].end_y - game->timer[SP_SEC].start_y;
	game->timer[SP_SEC].sec = 1;
}

void init_timer_pic(t_game *game)
{
	init_timer_bg_part(game);
    init_min_part(game);
    init_point_part(game);
    init_sec_part(game);
}
