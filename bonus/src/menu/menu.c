/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omben-ch <omben-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 09:49:46 by omben-ch          #+#    #+#             */
/*   Updated: 2025/09/13 18:35:35 by omben-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_bs.h"

void	draw_menu(t_game *game)
{
	if (game->end_start_menu == IN_PLY_I_VID)
		game->end_start_menu = START;
	if (game->end_start_menu == START)
	{
		put_bg(game, &game->graphic_menu[BG_IMG]);
		put_imag(game, &game->buttons[START]);
		put_imag(game, &game->buttons[CONTROL]);
		put_imag(game, &game->buttons[EXIT]);
	}
	if (game->end_start_menu == CONTROL)
	{
		put_bg(game, &game->graphic_menu[CONTROL_PAGE_IMG]);
		put_imag(game, &game->buttons[RETURN]);
	}
	if (game->end_start_menu == EXIT)
	{
		put_bg(game, &game->graphic_menu[EXIT_PAGE_IMG]);
		put_imag(game, &game->buttons[YES]);
		put_imag(game, &game->buttons[NO]);
	}
	mlx_put_image_to_window(game->mlx, game->win, game->display.img, 0, 0);
}

void	init_img_menu(t_game *game)
{
	game->end_start_menu = START;
	create_yes_button(game, &game->buttons[YES]);
	create_return_button(game, &game->buttons[RETURN]);
	create_no_button(game, &game->buttons[NO]);
	create_start_button(game, &game->buttons[START]);
	create_control_button(game, &game->buttons[CONTROL]);
	create_exit_button(game, &game->buttons[EXIT]);
}

void	put_pixel(t_game *game, int x, int y, int color)
{
	unsigned *color_add;
	if (x < 0 || y < 0 || x >= game->win_w || y >= game->win_h)
		return ;
	color_add = (unsigned *)(game->display.addr + (x * game->display.bpp / 8)
			+ (y * game->display.line_len));
	*color_add = color;
}

void	put_bg(t_game *game, t_image *img)
{
	t_var	v;

	v.scale_x = (double)img->w / (double)game->win_w;
	v.scale_y = (double)img->h / (double)game->win_h;
	v.y = 0;
	while (v.y < game->win_h)
	{
		v.x = 0;
		while (v.x < game->win_w)
		{
			v.img_x = (double)v.x * (double)v.scale_x;
			v.img_y = (double)v.y * (double)v.scale_y;
			v.color = *(unsigned *)(img->addr + (v.img_x * img->bpp / 8)
					+ (v.img_y * img->line_len));
			if (!get_t(v.color))
				put_pixel(game, v.x, v.y, v.color);
			v.x++;
		}
		v.y++;
	}
}

void	put_imag(t_game *game, t_button *img_info)
{
	t_var	v;

	v.scale_x = (double)img_info->img->w / (double)img_info->width;
	v.scale_y = (double)img_info->img->h / (double)img_info->height;
	v.y = 0;
	while (v.y < img_info->height)
	{
		v.x = 0;
		while (v.x < img_info->width)
		{
			v.img_x = (double)v.x * (double)v.scale_x;
			v.img_y = (double)v.y * (double)v.scale_y;
			v.color = *(unsigned *)(img_info->img->addr + (v.img_x
						* img_info->img->bpp / 8) + (v.img_y
						* img_info->img->line_len));
			if (!get_t(v.color))
				put_pixel(game, img_info->start_x + v.x, img_info->start_y
					+ v.y, v.color);
			v.x++;
		}
		v.y++;
	}
}
