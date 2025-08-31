/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   design.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omben-ch <omben-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 15:13:48 by omben-ch          #+#    #+#             */
/*   Updated: 2025/08/22 17:06:40 by omben-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_bs.h"

void	put_timer(t_game *game)
{
	put_imag(game, (t_button *)&game->timer[TIMER_BG]);
	put_time_imag(game, &game->timer[FP_MIN], game->timer[FP_MIN].min / 10 + 1);
	put_time_imag(game, &game->timer[SP_MIN], game->timer[FP_MIN].min % 10 + 1);
	put_imag(game, (t_button *)&game->timer[POINT]);
	put_time_imag(game, &game->timer[FP_SEC], game->timer[FP_SEC].sec / 10 + 1);
	put_time_imag(game, &game->timer[SP_SEC], game->timer[FP_SEC].sec % 10 + 1);
	mlx_put_image_to_window(game->mlx, game->win, game->display.img, 0, 0);
}
void	draw_timer(t_game *game)
{
	static long int tmp_time;
	long int time;

		init_timer_pic(game);
	while (1)
	{
		
		if (!tmp_time)
		{
			put_timer(game);
			tmp_time =  get_time_sec();
		}
		time = get_time_sec();
		if (time - tmp_time == 1)
		{
			game->timer[FP_SEC].sec++;
			tmp_time = time;
			put_timer(game);
		}
		if (game->timer[FP_SEC].sec == 60)
		{
			game->timer[FP_SEC].sec = 0;
			game->timer[FP_MIN].min++;
			put_timer(game);
		}

	}
}