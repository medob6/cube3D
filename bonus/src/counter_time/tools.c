/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omben-ch <omben-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 18:25:34 by omben-ch          #+#    #+#             */
/*   Updated: 2025/08/04 19:03:51 by omben-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void put_time_imag(t_game *game, t_timer *img_info , int index)
{
    unsigned color;
    double scale_x;
    double scale_y;
    double start_x;
    int img_y;
    int img_x;
    int y;
    int end;
    int x;
    /////////////////////////////////
    
    img_info->img = &game->graphic_menu[NUMBERS_IMG];
	img_info->start_x = 0;
	img_info->start_y = 0.1 * (game->win_h / 35);
	img_info->end_x = game->win_w / 35;
	img_info->end_y = (game->win_h / 35);
	img_info->width = img_info->end_x - img_info->start_x;
	img_info->height = img_info->end_y - img_info->start_y;
    
    /////////////////////////////////
    end = index * ((double)img_info->img->w / 10.0);
    start_x = (index-1)*((double)img_info->img->w / 10.0);
    scale_x = (double)end  / (double)img_info->width;
    scale_y = (double)img_info->img->h  / (double)img_info->height;
    //end = ((double)img_info->img->w / 10.0) + start_x;
    y = 0;
    while (y < img_info->height  * scale_y)
    {
        x = start_x;
        while (x < end)
        {
            img_x = (double)x ;
            img_y = (double)y ;
            color = *(unsigned *)(img_info->img->addr + (img_x * img_info->img->bpp / 8) + (img_y * img_info->img->line_len));
            if (!get_t(color))
                put_pixel(game,img_info->start_x + x, img_info->start_y + y,color);
            x++;
        }
        y++;
    }
}

int get_time_sec()
{
 	struct timeval time;

    gettimeofday(&time,NULL);
    return ((int)(time.tv_sec + (time.tv_usec / 10)));
}
