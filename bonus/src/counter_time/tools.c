/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omben-ch <omben-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 18:25:34 by omben-ch          #+#    #+#             */
/*   Updated: 2025/08/06 08:48:01 by omben-ch         ###   ########.fr       */
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
    end = index * ((double)img_info->img->w / 10.0);
    start_x = (index-1)*((double)img_info->img->w / 10.0);
    scale_x = (double)((double)img_info->img->w / 10.0)  / (double)img_info->width;
    scale_y = (double)img_info->img->h  / (double)img_info->height;
    y = 0;
    while (y < img_info->height)
    {
        x = 0;
        while (x < img_info->width)
        {
            img_x = (double)start_x+(x* scale_x);
            img_y = (double)y* scale_y;
            color = *(unsigned *)(img_info->img->addr + (img_x * img_info->img->bpp / 8) + (img_y * img_info->img->line_len));
            if (!get_t(color))
                put_pixel(game,img_info->start_x + x, img_info->start_y + y,color);
            x++;
        }
        y++;
    }
}

long int get_time_sec()
{
 	struct timeval time;

    gettimeofday(&time,NULL);
    return ((int)(time.tv_sec));
}
