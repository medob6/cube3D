/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall_slice.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbousset <mbousset@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 16:07:07 by mbousset          #+#    #+#             */
/*   Updated: 2025/09/08 14:31:34 by mbousset         ###   ########.fr       */
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

void	calc_boundaries(t_sec *slice, int w_x, int old_wh, t_draw_bounds *b)
{
	calculate_old_boundaries(old_wh, w_x, &b->old_wt, &b->old_wb);
	calculate_wall_boundaries(slice, w_x, &b->wall_top, &b->wall_bottom);
}

void	draw_wall_slice(int w_x, t_sec *slice, int old_wh)
{
	t_sec_inf		*section;
	t_draw_bounds	b;
	t_sec_params	p;

	calc_boundaries(slice, w_x, old_wh, &b);
	p = (t_sec_params){slice[w_x].wall_h, slice[w_x].wall_x, slice[w_x].dir,
		slice[w_x].door};
	section = init_section(w_x, p);
	apply_texture_offset(section, &b.wall_top);
	draw_ceiling_section(section, b.old_wt, b.wall_top);
	draw_wall_section(section, b.wall_top, b.wall_bottom);
	draw_floor_section(section, b.wall_bottom, b.old_wb);
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
	t_hit_data	h;
	t_door		the_door;

	the_door = (t_door){.pos.x = -1};
	h.x = horiz_dist(ang, &h.h_x, &h.h_dir, &the_door);
	h.y = verti_dist(ang, &h.v_x, &h.v_dir, &the_door);
	if (h.x < h.y)
	{
		fill_line_inf(line, h.h_dir, h.h_x, h.x);
		if (the_door.pos.x != -1)
			line->door = the_door;
	}
	else
	{
		fill_line_inf(line, h.v_dir, h.v_x, h.y);
		if (the_door.pos.y != -1)
			line->door = the_door;
	}
	return (correct_dist(line->raw_dist, ang));
}
