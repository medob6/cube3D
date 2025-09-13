/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omben-ch <omben-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 18:25:34 by omben-ch          #+#    #+#             */
/*   Updated: 2025/09/13 18:23:13 by omben-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_bs.h"

void	put_time_imag(t_game *game, t_timer *img_info, int index)
{
	t_var	v;

	v.start_x = (index - 1) * ((double)img_info->img->w / 10.0);
	v.scale_x = (double)((double)img_info->img->w / 10.0)
		/ (double)img_info->width;
	v.scale_y = (double)img_info->img->h / (double)img_info->height;
	v.y = 0;
	while (v.y < img_info->height)
	{
		v.x = 0;
		while (v.x < img_info->width)
		{
			v.img_x = (double)v.start_x + (v.x * v.scale_x);
			v.img_y = (double)v.y * v.scale_y;
			v.color = *(unsigned *)(img_info->img->addr + (v.img_x
						* img_info->img->bpp / 8) + (v.img_y
						* img_info->img->line_len));
			if (!get_t(v.color))
				put_timer_pixel(game, img_info->start_x + v.x, img_info->start_y
					+ v.y, v.color);
			v.x++;
		}
		v.y++;
	}
}

long int	get_time_sec(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((int)(time.tv_sec));
}
