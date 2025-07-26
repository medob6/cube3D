/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_color.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbousset <mbousset@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 15:51:51 by mbousset          #+#    #+#             */
/*   Updated: 2025/07/14 16:24:22 by mbousset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycaster.h"

t_sec_inf	*init_section(int w_x, double wall_h, int x, t_graphic dir)
{
	t_sec_inf	*section;

	section = malloc(sizeof(t_sec_inf));
	section->sec.wall_h = wall_h;
	section->sec.dir = dir;
	section->sec.wall_x = x;
	section->win_x = w_x;
	section->tex_offset = 0;
	return (section);
}

unsigned int	get_slice_color(int x, int y, int dir, int section)
{
	if (section == 1)
		return (get_game()->data.ceiling_clr);
	else if (section == 2)
	{
		if (dir == -1)
			return (0x000000);
		if ((x >= 0 && x < get_game()->graphics[dir].w) && (y >= 0
				&& y < get_game()->graphics[dir].h))
			return (get_color(get_game()->graphics[dir], x, y));
	}
	else if (section == 3)
		return (get_game()->data.floor_clr);
	return (0xffffff);
}

void	draw_section(int start, int end, int num, t_sec_inf *section)
{
	int		i;
	t_image	tex;
	double	d_from_top;
	int		color;
	t_point	tex_p;
	double	hight_factur;
	int		offset;

	if (num == 2 && section->sec.dir != -1)
	{
		tex = get_game()->graphics[section->sec.dir];
		offset = -start + section->tex_offset;
		hight_factur = tex.h / section->sec.wall_h;
		tex_p.x = fmod(section->sec.wall_x, WALL_WIDTH) / WALL_WIDTH * tex.w;
	}
	i = start--;
	end = fmin(end, get_game()->win_h);
	while (++i <= end)
	{
		if (num == 2)
		{
			d_from_top = i + offset;
			tex_p.y = d_from_top * hight_factur;
		}
		color = get_slice_color(tex_p.x, tex_p.y, section->sec.dir, num);
		my_mlx_pixel_put(get_game()->display, section->win_x, i, color);
	}
}

bool	in_minimap_range(int w_x)
{
	int	minimap_r;
	int	minima_c;
	int	var;

	minimap_r = get_game()->win_h * MINIMAP_SCREEN_SCALE;
	minima_c = minimap_r * 1.2;
	var = minimap_r + minimap_r * ICON_SCALE * 2;
	if (w_x < minima_c + var && w_x > minima_c - var)
		return (true);
	return (false);
}

void	calculate_old_boundaries(int old_wh, int w_x, int *old_wt, int *old_wb)
{
	*old_wt = (get_game()->win_h / 2 - old_wh / 2 - 1) * (old_wh != 0);
	*old_wb = *old_wt + old_wh;
	if (old_wh == 0 || in_minimap_range(w_x))
		*old_wb = get_game()->win_h;
	if (*old_wt < 0)
		*old_wt = 0;
}
