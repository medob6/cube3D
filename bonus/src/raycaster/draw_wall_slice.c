/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall_slice.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbousset <mbousset@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 16:07:07 by mbousset          #+#    #+#             */
/*   Updated: 2025/08/08 18:41:07 by mbousset         ###   ########.fr       */
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
	// printf("slice2 frame nbr = %d \n", slice->door.frame);
	section = init_section(w_x, slice[w_x].wall_h, slice[w_x].wall_x,
			slice[w_x].dir, slice[w_x].door);
	apply_texture_offset(section, &wall_top);
	draw_ceiling_section(section, old_wt, wall_top);
	draw_wall_section(section, wall_top, wall_bottom);
	draw_floor_section(section, wall_bottom, old_wb);
	// if (player view intersect with door)
	// 	render door
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

double	closest_hit(double ang, t_sec *line)
{
	static int	i;
	t_pair		distance;
	double		h_x;
	double		v_x;
	int			h_dir;
	int			v_dir;
	int			n;
	bool		can_open;

	int door_x, door_y;
	can_open = false;
	h_dir = -1;
	v_dir = -1;
	distance.x = horiz_dist(ang, &h_x, &h_dir);
	distance.y = verti_dist(ang, &v_x, &v_dir);
	if (distance.x < distance.y)
		fill_line_inf(line, h_dir, h_x, distance.x);
	else
		fill_line_inf(line, v_dir, v_x, distance.y);
	if (line->dir == DOOR)
	{
		if (ang > (get_game()->player.angle - FOV_ANGLE / 6)
			&& ang < (get_game()->player.angle + FOV_ANGLE / 6))
		{
			if ((line->raw_dist * cos(normalize_angle(ang
							- get_game()->player.angle))) <= WALL_WIDTH)
			{
				if (fmod(line->wall_x, WALL_WIDTH) <= WALL_WIDTH / 3 * 2
					&& fmod(line->wall_x, WALL_WIDTH) >= WALL_WIDTH / 3)
					can_open = true;
			}
		}
		if (distance.x < distance.y)
		{
			door_x = (int)(line->wall_x / WALL_WIDTH);
			door_y = (int)((get_game()->player.p.y + distance.x * sin(ang))
					/ WALL_WIDTH);
		}
		else
		{
			door_y = (int)(line->wall_x / WALL_WIDTH);
			door_x = (int)((get_game()->player.p.x + distance.y * cos(ang))
					/ WALL_WIDTH);
		}
		n = 0;
		while (n < get_game()->nb_of_doors)
		{
			if ((door_y == (int)get_game()->doors[n].pos.y)
				&& (door_x == (int)get_game()->doors[n].pos.x))
			{
				line->door = get_game()->doors[n];
				get_game()->doors[n].open = get_game()->doors[n].open
					|| can_open;
			}
			n++;
		}
	}
	return (line->raw_dist * cos(normalize_angle(ang
				- get_game()->player.angle)));
}
