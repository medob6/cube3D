/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_of_player.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omben-ch <omben-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 18:25:30 by omben-ch          #+#    #+#             */
/*   Updated: 2025/09/02 11:57:25 by omben-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_bs.h"


void	put_timer_pixel(t_game *game, int x, int y, int color)
{
	unsigned	*color_add;

	if (x < 0 || y < 0 || x >= game->win_timer_w || y >= game->win_timer_h)
		return ;
	color_add = (unsigned *)(game->img_timer.addr + (x * game->img_timer.bpp / 8)
			+ (y * game->img_timer.line_len));
	*color_add = color;
}

void	put_timer_bg(t_game *game, t_image *img)
{
	int			y;
	int			x;
	int			img_x;
	int			img_y;
	unsigned	color;
	double		scale_x;
	double		scale_y;

	scale_x = (double)img->w / (double)game->win_timer_w;
	scale_y = (double)img->h / (double)game->win_timer_h;
	y = 0;
	while (y < game->win_timer_h)
	{
		x = 0;
		while (x < game->win_timer_w)
		{
			img_x = (double)x * (double)scale_x;
			img_y = (double)y * (double)scale_y;
			color = *(unsigned *)(game->display.addr + (x * game->display.bpp / 8)
			+ (y * game->display.line_len));
			if (!get_t(color))
				put_timer_pixel(game, x, y, color);
			x++;
		}
		y++;
	}
}

void	put_timer_imag(t_game *game, t_button *img_info)
{
	int			img_x;
	int			y;
	int			x;
	int			img_y;
	unsigned	color;
	double		scale_x;
	double		scale_y;

	scale_x = (double)img_info->img->w / (double)img_info->width;
	scale_y = (double)img_info->img->h / (double)img_info->height;
	y = 0;
	while (y < img_info->height)
	{
		x = 0;
		while (x < img_info->width)
		{
			img_x = (double)x * (double)scale_x;
			img_y = (double)y * (double)scale_y;
			color = *(unsigned *)(img_info->img->addr + (img_x
						* img_info->img->bpp / 8) + (img_y
						* img_info->img->line_len));
			if (!get_t(color))
				put_timer_pixel(game, img_info->start_x + x, img_info->start_y + y,
					color);
			x++;
		}
		y++;
	}
}
