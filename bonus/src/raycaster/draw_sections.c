/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbousset <mbousset@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 16:07:04 by mbousset          #+#    #+#             */
/*   Updated: 2025/07/31 10:04:57 by mbousset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycaster_bs.h"

void	calculate_wall_boundaries(t_sec *slice, int w_x, int *wall_top,
		int *wall_bottom)
{
	*wall_top = get_game()->win_h / 2 - slice[w_x].wall_h / 2
		+ get_game()->player.p.z;
	*wall_bottom = *wall_top + slice[w_x].wall_h;
	if (*wall_bottom > get_game()->win_h)
		*wall_bottom = get_game()->win_h;
}

void	apply_texture_offset(t_sec_inf *section, int *wall_top)
{
	if (*wall_top < 0)
	{
		section->tex_offset = -*wall_top;
		*wall_top = 0;
	}
}

void	draw_ceiling_section(t_sec_inf *section, int old_wt, int wall_top)
{
	if (old_wt < wall_top)
		draw_section(old_wt, wall_top, 1, section);
}

void	draw_wall_section(t_sec_inf *section, int wall_top, int wall_bottom)
{
	draw_section(wall_top, wall_bottom, 2, section);
}

void	draw_floor_section(t_sec_inf *section, int wall_bottom, int old_wb)
{
	if (wall_bottom < old_wb)
		draw_section(wall_bottom, old_wb, 3, section);
}
