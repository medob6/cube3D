/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   design.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omben-ch <omben-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 15:13:48 by omben-ch          #+#    #+#             */
/*   Updated: 2025/09/13 18:23:52 by omben-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_bs.h"
#include "video_bs.h"

void	restart_game(t_game *game)
{
	init_resources_game(game);
	game->passed = false;
	game->timer[FP_SEC].sec = 60;
	game->timer[FP_MIN].min = game->toeg;
	game->end_start_menu = START;
	game->win_lose = 0;
	game->tmp_time = 0;
	draw_menu(game);
}

void	put_timer(t_game *game, int sign)
{
	put_timer_bg(game, game->timer[TIMER_BG].img);
	put_time_imag(game, &game->timer[FP_MIN], game->timer[FP_MIN].min / 10 + 1);
	put_time_imag(game, &game->timer[SP_MIN], game->timer[FP_MIN].min % 10 + 1);
	put_timer_imag(game, &game->timer[POINT]);
	put_time_imag(game, &game->timer[FP_SEC], game->timer[FP_SEC].sec / 10 + 1);
	put_time_imag(game, &game->timer[SP_SEC], game->timer[FP_SEC].sec % 10 + 1);
	mlx_put_image_to_window(game->mlx, game->win, game->img_timer.img, 0, 0);
}

void	draw_timer(t_game *game, int sign)
{
	long int	time;

	if (!game->tmp_time)
		game->tmp_time = get_time_sec();
	time = get_time_sec();
	if (time - game->tmp_time == 1)
	{
		game->timer[FP_SEC].sec--;
		game->tmp_time = time;
	}
	if (game->timer[FP_SEC].sec == 0 && game->timer[FP_MIN].min == 0)
	{
		put_timer(game, sign);
		game->win_lose = 2;
		return ;
	}
	if (game->timer[FP_SEC].sec == 0)
	{
		game->timer[FP_SEC].sec = 60;
		game->timer[FP_MIN].min--;
	}
	put_timer(game, sign);
}
