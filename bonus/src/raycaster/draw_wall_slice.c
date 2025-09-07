/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall_slice.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbousset <mbousset@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 16:07:07 by mbousset          #+#    #+#             */
/*   Updated: 2025/09/07 15:58:44 by mbousset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycaster_bs.h"

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
			slice[w_x].dir, slice[w_x].door);
	apply_texture_offset(section, &wall_top);
	draw_ceiling_section(section, old_wt, wall_top);
	draw_wall_section(section, wall_top, wall_bottom);
	draw_floor_section(section, wall_bottom, old_wb);
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
		if (ray > -offset)
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

double	correct_dist(double raw_d, double ang)
{
	return (raw_d * cos(normalize_angle(ang - get_game()->player.angle)));
}

double	closest_hit(double ang, t_sec *line)
{
	t_pair	distance;
	double	h_x;
	double	v_x;
	int		h_dir;
	int		v_dir;
	t_door	next_door_x;
	t_door	next_door_y;

	next_door_x = (t_door){.pos.x = -1};
	next_door_y = (t_door){.pos.x = -1};
	distance.x = horiz_dist(ang, &h_x, &h_dir, &next_door_x);
	distance.y = verti_dist(ang, &v_x, &v_dir, &next_door_y);
	if (distance.x < distance.y)
	{
		fill_line_inf(line, h_dir, h_x, distance.x);
		if (next_door_x.pos.x != -1)
			line->door = next_door_x;
	}
	else
	{
		fill_line_inf(line, v_dir, v_x, distance.y);
		if (next_door_y.pos.y != -1)
			line->door = next_door_y;
	}
	return (correct_dist(line->raw_dist, ang));
}
