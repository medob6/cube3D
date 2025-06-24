/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbousset <mbousset@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/24 18:19:30 by mbousset          #+#    #+#             */
/*   Updated: 2025/06/24 18:20:10 by mbousset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

double	normalize_angle(double angle)
{
	angle = fmod(angle, 2 * M_PI);
	if (angle < 0)
		angle += 2 * M_PI;
	return (angle);
}

double	get_distance(t_point a, t_point b)
{
	double	dist;

	dist = fabs(sqrt(pow(b.x, 2) + pow(b.y, 2)) - sqrt(pow(a.x, 2) + pow(a.y,
					2)));
	return (dist);
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
	char	*dst;

	if (x < 0 || y < 0 || x >= WIN_WIDTH || y >= WIN_HEIGHT)
		return ;
	dst = fram.addr + (y * fram.line_len + x * 4);
	*(unsigned int *)dst = color;
}
