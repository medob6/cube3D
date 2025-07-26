/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omben-ch <omben-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 09:49:46 by omben-ch          #+#    #+#             */
/*   Updated: 2025/07/26 18:14:01 by omben-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"
#define WIDTH 100
#define  HEIGHT 90

void init_img_menu(t_game *game)
{
    // double scale;

    
    game->list[0].img = &game->graphics[START];
	game->list[0].start_x = 5*(game->win_w/ 8);
	game->list[0].start_y = (game->win_h/ 8)*3;
    game->list[0].width = game->win_w *2/ 8;
	game->list[0].height = game->win_h/ 8;
	game->list[0].end_x = game->list[0].start_x + game->list[0].width;
	game->list[0].end_y = game->list[0].start_y + game->list[0].height;
    
	game->list[1].img = &game->graphics[CONTROL];
	game->list[1].start_x = 5*(game->win_w/ 8);
	game->list[1].start_y = (game->win_h/ 8)*4;
	game->list[1].end_x = game->win_w - ((game->win_w/ 8));
	game->list[1].end_y = (game->win_h / 8) * 5;
	game->list[1].width = game->list[1].end_x - game->list[1].start_x;
	game->list[1].height = game->list[1].end_y - game->list[1].start_y;
	
    game->list[2].img = &game->graphics[EXIT];
	game->list[2].start_x = 5*(game->win_w/ 8);
	game->list[2].start_y = (game->win_h/ 8)*5;
	game->list[2].end_x = game->win_w - ((game->win_w/ 8));
	game->list[2].end_y = (game->win_h / 8) * 6;
	game->list[2].width = game->list[2].end_x - game->list[2].start_x;
	game->list[2].height = game->list[2].end_y - game->list[2].start_y;
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

void put_bg(t_game *game, t_image *img)
{
    int y;
    int x;
    int img_x;
    int img_y;
    unsigned color;
    double scale_x;
    double scale_y;

    scale_x = (double)img->w  / (double)game->win_w;
    scale_y = (double)img->h  / (double)game->win_h;
    y = 0;
    while (y < game->win_h)
    {
        x = 0;
        while (x < game->win_w)
        {
            
            img_x = (double)x * (double)scale_x;    
            img_y = (double)y * (double)scale_y;
            color = *(unsigned *)(img->addr + (img_x * img->bpp / 8) + (img_y * img->line_len));
            if (color != 4278190080)
                put_pixel(game,x, y,color);
            x++;
        }
        y++;
    }
}

void put_imag(t_game *game, t_put_img_info *img_info)
{
    int img_x;
    int y;
    int x;
    int img_y;
    unsigned color;
    double scale_x;
    double scale_y;

    scale_x = (double)img_info->img->w  / (double)img_info->width;
    scale_y = (double)img_info->img->h  / (double)img_info->height;
    y = 0;
    while (y < img_info->height)
    {
        x = 0;
        while (x < img_info->width)
        {
            
            img_x = (double)x * (double)scale_x;    
            img_y = (double)y * (double)scale_y;
            color = *(unsigned *)(img_info->img->addr + (img_x * img_info->img->bpp / 8) + (img_y * img_info->img->line_len));
            if (color != 4278190080)
                put_pixel(game,img_info->start_x + x, img_info->start_y + y,color);
            x++;
        }
        y++;
    }
}
