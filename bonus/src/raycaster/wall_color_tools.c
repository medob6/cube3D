/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_color_tools.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbousset <mbousset@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 16:11:07 by omben-ch          #+#    #+#             */
/*   Updated: 2025/09/18 09:33:15 by mbousset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycaster_bs.h"

void	get_world_coords(t_floorcast *fc, double rowDist, double *worldx,
		double *worldy)
{
	double	factor;
	double	raydirx;
	double	raydiry;

	factor = (double)fc->win_x / fc->winw;
	raydirx = fc->raydirx0 + factor * (fc->raydirx1 - fc->raydirx0);
	raydiry = fc->raydiry0 + factor * (fc->raydiry1 - fc->raydiry0);
	*worldx = (fc->game->player.p.x / WALL_WIDTH) + rowDist * raydirx;
	*worldy = (fc->game->player.p.y / WALL_WIDTH) + rowDist * raydiry;
}

int	get_tex_color(t_floorcast *fc, t_point world_p, double rowDist, int num)
{
	int	tx;
	int	ty;
	int	color;

	if (num == 1)
	{
		if (!fc->sky_tex.img)
			return (get_game()->data.ceiling_clr);
		tx = ((int)(world_p.x * fc->sky_tex.w) % fc->sky_tex.w + fc->sky_tex.w) % fc->sky_tex.w;
		ty = ((int)(world_p.y * fc->sky_tex.h) % fc->sky_tex.h + fc->sky_tex.h)
			% fc->sky_tex.h;
		color = get_color(fc->sky_tex, tx, ty);
		color = apply_shading(color, rowDist * 100.0);
	}
	else
	{
		if (!fc->floor_tex.img)
			return (get_game()->data.floor_clr);
		tx = ((int)(world_p.x * fc->floor_tex.w) % fc->floor_tex.w
				+ fc->floor_tex.w) % fc->floor_tex.w;
		ty = ((int)(world_p.y * fc->floor_tex.h) % fc->floor_tex.h
				+ fc->floor_tex.h) % fc->floor_tex.h;
		color = get_color(fc->floor_tex, tx, ty);
		color = apply_shading(color, rowDist * 300.0);
	}
	return (color);
}
