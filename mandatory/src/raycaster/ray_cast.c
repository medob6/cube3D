/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbousset <mbousset@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 15:39:30 by mbousset          #+#    #+#             */
/*   Updated: 2025/07/12 16:06:24 by mbousset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycaster.h"

double	get_previous_wall_height(t_raycaster *c, int ray_index)
{
	return (c->prev_lines[ray_index].wall_h);
}

static inline void	swap_buffers(t_raycaster *c)
{
	t_sec	*tmp;

	tmp = c->prev_lines;
	c->prev_lines = c->lines;
	c->lines = tmp;
}

void	process_all_rays(t_raycaster *c, t_frame_state *state)
{
	int		i;
	double	old_wh;

	i = -1;
	while (++i < c->num_rays)
	{
		old_wh = get_previous_wall_height(c, i);
		process_ray(c, state, i);
		draw_wall_slice(i, c->lines, old_wh);
	}
}

void	draw_3d_view(t_game *g, t_raycaster *c)
{
	t_frame_state	state;

	init_frame_state(g, c, &state);
	process_all_rays(c, &state);
	swap_buffers(c);
}

void	display_scean(t_game *game)
{
	static bool			first = true;
	static t_raycaster	caster;

	if (first)
	{
		init_raycaster(&caster);
		first = false;
	}
	draw_3d_view(game, &caster);
}
