/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omben-ch <omben-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 18:19:30 by mbousset          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2025/08/20 10:23:31 by omben-ch         ###   ########.fr       */
=======
/*   Updated: 2025/08/02 09:51:35 by mbousset         ###   ########.fr       */
>>>>>>> 384d2b3a7c05f5be84a9a9f5ccc1ea2d1e67dafe
/*                                                                            */
/* ************************************************************************** */

#include "cub_bs.h"

double	normalize_angle(double angle)
{
	angle = fmod(angle, 2 * M_PI);
	if (angle < 0)
		angle += 2 * M_PI;
	return (angle);
}

void	get_window_dimensions(void)
{
	t_game	*game;
	int		w;
	int		h;

	game = get_game();
	mlx_get_screen_size(game->mlx, &w, &h);
	game->win_w = w * 0.7;
	game->win_h = h * 0.7;
}

int	get_t(int trgb)
{
	return ((trgb >> 24) & 0xFF);
}

unsigned int	get_color(t_image img, int x, int y)
{
	int	offset;

	offset = (y * img.line_len) + (x * (img.bpp / 8));
	return (*(unsigned int *)(img.addr + offset));
}

void	my_mlx_pixel_put(t_image fram, int x, int y, int color)
{
	char *dst;
	t_game *game;
	game = get_game();
	if (x < 0 || y < 0 || x >= game->win_w || y >= game->win_h)
		return ;
	dst = fram.addr + (y * fram.line_len) + (x * fram.bpp / 8);
	*(unsigned int *)dst = color;
}