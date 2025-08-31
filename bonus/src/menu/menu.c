/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omben-ch <omben-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 09:49:46 by omben-ch          #+#    #+#             */
/*   Updated: 2025/08/22 17:06:40 by omben-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_bs.h"

int	check_button(t_game *game, int x, int y)
{
	int	i;

	i = -1;
	while (++i < NB_BUTTON)
	{
		if ((x >= game->buttons[i].start_x && x <= game->buttons[i].end_x)
			&& (y >= game->buttons[i].start_y && y <= game->buttons[i].end_y))
			return (i);
	}
	return (-1);
}

void	draw_menu(t_game *game)
{
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
	unsigned	*color_add;

	if (x < 0 || y < 0 || x >= game->win_w || y >= game->win_h)
		return ;
	color_add = (unsigned *)(game->display.addr + (x * game->display.bpp / 8)
			+ (y * game->display.line_len));
	*color_add = color;
}

void	put_bg(t_game *game, t_image *img)
{
	int			y;
	int			x;
	int			img_x;
	int			img_y;
	unsigned	color;
	double		scale_x;
	double		scale_y;

	scale_x = (double)img->w / (double)game->win_w;
	scale_y = (double)img->h / (double)game->win_h;
	y = 0;
	while (y < game->win_h)
	{
		x = 0;
		while (x < game->win_w)
		{
			img_x = (double)x * (double)scale_x;
			img_y = (double)y * (double)scale_y;
			color = *(unsigned *)(img->addr + (img_x * img->bpp / 8) + (img_y
						* img->line_len));
			if (!get_t(color))
				put_pixel(game, x, y, color);
			x++;
		}
		y++;
	}
}

void	put_imag(t_game *game, t_button *img_info)
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
				put_pixel(game, img_info->start_x + x, img_info->start_y + y,
					color);
			x++;
		}
		y++;
	}
}
