/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   design.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omben-ch <omben-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 15:13:48 by omben-ch          #+#    #+#             */
/*   Updated: 2025/09/02 15:43:25 by omben-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_bs.h"

void	put_timer(t_game *game ,int sign)
{
	put_timer_bg(game, game->timer[TIMER_BG].img);
	put_time_imag(game, &game->timer[FP_MIN], game->timer[FP_MIN].min / 10 + 1);
	put_time_imag(game, &game->timer[SP_MIN], game->timer[FP_MIN].min % 10 + 1);
	put_timer_imag(game, (t_button *)&game->timer[POINT]);
	put_time_imag(game, &game->timer[FP_SEC], game->timer[FP_SEC].sec / 10 + 1);
	put_time_imag(game, &game->timer[SP_SEC], game->timer[FP_SEC].sec % 10 + 1);
	mlx_put_image_to_window(game->mlx, game->win, game->img_timer.img , 0, 0);
}
void	draw_timer(t_game *game, int sign)
{
	static long int tmp_time;
	long int time;
	
	if (!tmp_time)
		tmp_time =  get_time_sec();
	time = get_time_sec();
	if (time - tmp_time == 1)
	{
		game->timer[FP_SEC].sec++;
		tmp_time = time;
	}
	if (game->timer[FP_SEC].sec == 60)
	{
		game->timer[FP_SEC].sec = 0;
		game->timer[FP_MIN].min++;
	}
	if (game->timer[FP_SEC].sec == 8)
	{
		handle_close();
	}
	put_timer(game, sign);
}
