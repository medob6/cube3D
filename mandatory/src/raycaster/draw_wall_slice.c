/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall_slice.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbousset <mbousset@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 16:07:07 by mbousset          #+#    #+#             */
/*   Updated: 2025/09/15 15:23:41 by mbousset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycaster.h"

void	draw_jump_floor_section(t_sec_inf *section, int wall_bottom, int old_wb)
{
	int	jump_floor_end;

	if (get_game()->player.jumping)
	{
		jump_floor_end = old_wb + get_game()->player.p.z + JUMP_SPEED + 5;
		draw_section(wall_bottom, jump_floor_end, 3, section);
	}
}

void	draw_wall_slice(int w_x, t_sec *slice, int old_wh)
{
	t_sec_inf	*section;
	int			wall_top;
	int			wall_bottom;
	int			old_wt;
	int			old_wb;

	calculate_old_boundaries(old_wh, w_x, &old_wt, &old_wb);
	calculate_wall_boundaries(slice, w_x, &wall_top, &wall_bottom);
	section = init_section(w_x, slice[w_x].wall_h, slice[w_x].wall_x,
			slice[w_x].dir);
	apply_texture_offset(section, &wall_top);
	draw_ceiling_section(section, old_wt, wall_top);
	draw_wall_section(section, wall_top, wall_bottom);
	draw_floor_section(section, wall_bottom, old_wb);
	draw_jump_floor_section(section, wall_bottom, old_wb);
	free(section);
}

bool	check_in_range(int ray, int offset, int max_rays)
{
	if (offset > 0)
	{
		if (ray < max_rays - offset)
			return (true);
	}
	else if (offset < 0)
	{
		if (ray >= -offset)
			return (true);
	}
	return (false);
}

void	fill_line_inf(t_sec *line, int dir, double wall_x, double dist)
{
	line->dir = dir;
	line->wall_x = wall_x;
	line->raw_dist = dist;
}

double	closest_hit(double ang, t_sec *line)
{
	t_pair	distance;
	double	h_x;
	double	v_x;
	int		h_dir;
	int		v_dir;

	h_dir = -1;
	v_dir = -1;
	distance.x = horiz_dist(ang, &h_x, &h_dir);
	distance.y = verti_dist(ang, &v_x, &v_dir);
	if (distance.x < distance.y)
		fill_line_inf(line, h_dir, h_x, distance.x);
	else
		fill_line_inf(line, v_dir, v_x, distance.y);
	return (line->raw_dist * cos(normalize_angle(ang
				- get_game()->player.angle)));
}
