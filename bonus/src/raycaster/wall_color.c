/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_color.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omben-ch <omben-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 15:51:51 by mbousset          #+#    #+#             */
/*   Updated: 2025/09/16 14:48:10 by omben-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycaster_bs.h"

void	draw_wall(int start, int end, t_sec_inf *section, int num)
{
	t_wall_inf	inf;
	double		d_from_top;
	int			color;
	int			i;

	initialize_wall_inf(&inf, section, start);
	i = start - 1;
	while (++i <= end && i < inf.win_h)
	{
		d_from_top = i + inf.offset;
		inf.tex_p.y = d_from_top * inf.h_factor;
		color = get_slice_color(inf.tex_p.x, inf.tex_p.y, section->sec.dir,
				num);
		color = apply_shading(color, inf.raw_dist);
		if (get_t(color) != 255)
			my_mlx_pixel_put(get_game()->display, section->win_x, i, color);
	}
}

static void	draw_floor_ceiling(t_floorcast *fc, int start, int end, int num)
{
	int		y;
	double	p;
	double	rowdist;
	t_point	world_p;
	int		color;

	y = start - 1;
	while (++y <= end && y < fc->winh)
	{
		p = (double)y - fc->mid;
		if (p == 0.0)
			continue ;
		rowdist = fc->eyeheight / fabs(p);
		get_world_coords(fc, rowdist, &world_p.x, &world_p.y);
		color = get_tex_color(fc, world_p, rowdist, num);
		my_mlx_pixel_put(fc->game->display, fc->win_x, y, color);
	}
}

void	draw_section(int start, int end, int num, t_sec_inf *section)
{
	t_floorcast	fc;

	if (num == 2 && section->sec.dir != -1)
	{
		draw_wall(start, end, section, num);
		return ;
	}
	if (num != 1 && num != 3)
		return ;
	fc = init_floorcast(section);
	draw_floor_ceiling(&fc, start, end, num);
}

void	calculate_old_boundaries(int old_wh, int w_x, int *old_wt, int *old_wb)
{
	*old_wt = (get_game()->win_h / 2 - old_wh / 2 + get_game()->player.p.z)
		* (old_wh != 0);
	*old_wb = *old_wt + old_wh;
	if (old_wh == 0 || in_minimap_range(w_x))
		*old_wb = get_game()->win_h;
	if (*old_wt < 0)
		*old_wt = 0;
}
