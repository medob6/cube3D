/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frame_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbousset <mbousset@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 15:55:45 by mbousset          #+#    #+#             */
/*   Updated: 2025/07/29 18:44:15 by mbousset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycaster.h"

void	init_frame_state(t_game *g, t_raycaster *c, t_frame_state *state)
{
	state->pos_changed = check_position(g);
	state->old_ang = get_old_angel(g);
	state->ray_offset = 0;
	if (state->old_ang != g->player.angle)
		state->ray_offset = (g->player.angle - state->old_ang) / c->angle_step;
	state->start_angle = g->player.angle - FOV_ANGLE / 2;
	state->proj_dist = (g->win_w / 2) / tan(FOV_ANGLE / 2);
}

double	calculate_ray_angle(t_frame_state *state, t_raycaster *c, int ray_index)
{
	return (normalize_angle(state->start_angle + ray_index * c->angle_step));
}

bool	can_reuse_ray(t_frame_state *state, t_raycaster *c, int ray_index)
{
	return (!state->pos_changed && check_in_range(ray_index, state->ray_offset,
			c->num_rays));
}

void	reuse_ray_data(t_raycaster *c, t_frame_state *state, int ray_index,
		double ray_ang)
{
	double	corrected_dist;

	c->lines[ray_index] = c->prev_lines[ray_index + state->ray_offset];
	corrected_dist = c->lines[ray_index].raw_dist * cos(normalize_angle(ray_ang - get_game()->player.angle));
	c->lines[ray_index].wall_h = (WALL_HIGHT / corrected_dist) * state->proj_dist;
}

void	cast_new_ray(t_raycaster *c, t_frame_state *state, int ray_index,
		double ray_ang)
{
	double	d;

	d = closest_hit(ray_ang, &c->lines[ray_index]);
	c->lines[ray_index].wall_h = (WALL_HIGHT / d) * state->proj_dist;
}
