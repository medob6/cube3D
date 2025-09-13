/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_of_player.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omben-ch <omben-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 18:25:30 by omben-ch          #+#    #+#             */
/*   Updated: 2025/09/13 18:57:36 by omben-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_bs.h"

void	put_timer_pixel(t_game *game, int x, int y, int color)
{
	unsigned *color_add;
	if (x < 0 || y < 0 || x >= game->win_timer_w || y >= game->win_timer_h)
		return ;
	color_add = (unsigned *)(game->img_timer.addr + (x * game->img_timer.bpp
				/ 8) + (y * game->img_timer.line_len));
	*color_add = color;
}

void	put_timer_bg(t_game *game, t_image *img)
{
	t_var	v;

	v.scale_x = (double)img->w / (double)game->win_timer_w;
	v.scale_y = (double)img->h / (double)game->win_timer_h;
	v.y = 0;
	while (v.y < game->win_timer_h)
	{
		v.x = -1;
		while (++v.x < game->win_timer_w)
		{
			v.img_x = (double)v.x * (double)v.scale_x;
			v.img_y = (double)v.y * (double)v.scale_y;
			v.color = *(unsigned *)(game->display.addr + (v.x
						* game->display.bpp / 8) + (v.y
						* game->display.line_len));
			if (!get_t(v.color))
				put_timer_pixel(game, v.x, v.y, v.color);
		}
		v.y++;
	}
}

unsigned int	get_pixel_color(t_timer *img_info, int img_x, int img_y)
{
	return (*(unsigned *)(img_info->img->addr + (img_x * img_info->img->bpp / 8)
		+ (img_y * img_info->img->line_len)));
}

void	put_timer_imag(t_game *game, t_timer *img_info)
{
	t_var	v;

	v.scale_x = (double)img_info->img->w / (double)img_info->width;
	v.scale_y = (double)img_info->img->h / (double)img_info->height;
	v.y = -1;
	while (++v.y < img_info->height)
	{
		v.x = -1;
		while (++v.x < img_info->width)
		{
			v.img_x = (double)v.x * (double)v.scale_x;
			v.img_y = (double)v.y * (double)v.scale_y;
			v.color = get_pixel_color(img_info, v.img_x, v.img_y);
			if (!get_t(v.color))
				put_timer_pixel(game, img_info->start_x + v.x, img_info->start_y
					+ v.y, v.color);
		}
	}
}
