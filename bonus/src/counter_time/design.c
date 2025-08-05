/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   design.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omben-ch <omben-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/05 15:13:48 by omben-ch          #+#    #+#             */
/*   Updated: 2025/08/05 18:58:39 by omben-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void draw_timer(t_game *game)
{
    init_timer_pic(game);
    put_imag(game,(t_button *)&game->timer[TIMER_BG]);
    put_time_imag(game,&game->timer[FP_MIN],game->timer[FP_MIN].min / 10 + 1);
    put_time_imag(game,&game->timer[SP_MIN],game->timer[SP_MIN].min % 10 + 1);
    put_imag(game,(t_button *)&game->timer[POINT]);
    put_time_imag(game,&game->timer[FP_SEC],game->timer[FP_MIN].min / 10 + 1);
    put_time_imag(game,&game->timer[SP_SEC],game->timer[FP_MIN].min % 10 + 1);
}