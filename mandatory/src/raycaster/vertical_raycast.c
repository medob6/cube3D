/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vertical_raycast.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbousset <mbousset@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 15:49:58 by mbousset          #+#    #+#             */
/*   Updated: 2025/07/12 16:12:47 by mbousset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycaster.h"

void	process_ray(t_raycaster *c, t_frame_state *state, int ray_index)
{
	double	ray_ang;

	ray_ang = calculate_ray_angle(state, c, ray_index);
	if (can_reuse_ray(state, c, ray_index))
		reuse_ray_data(c, state, ray_index, ray_ang);
	else
		cast_new_ray(c, state, ray_index, ray_ang);
}

void	get_steps_v(t_pair *step, bool left, double ray_ang)
{
	step->x = TILE_SIZE * (-left + !left);
	step->y = step->x * tan(ray_ang);
}

void	get_v_inter(t_point *next, bool left, double ray_ang)
{
	next->x = floor(get_game()->player.p.x / TILE_SIZE) * TILE_SIZE;
	if (!left)
		next->x += TILE_SIZE;
	next->y = get_game()->player.p.y + (next->x - get_game()->player.p.x)
		* tan(ray_ang);
}

double	verti_dist(double ray_ang, double *wall_x, int *dir)
{
	t_point			map_p;
	t_point			next;
	t_pair			step;
	bool			left;
	const t_game	*g = get_game();

	left = cos(ray_ang) < 0;
	get_v_inter(&next, left, ray_ang);
	get_steps_v(&step, left, ray_ang);
	while (true)
	{
		map_p.x = ((next.x - 1) * (left) + next.x * (!left)) / TILE_SIZE;
		map_p.y = next.y / TILE_SIZE;
		if (outside_map(map_p.x, map_p.y))
			break ;
		if (g->data.map.arr[(int)map_p.y][(int)map_p.x] == '1')
			return (*wall_x = next.y, *dir = W_WALL * left + E_WALL * !left,
				get_dist(g->player.p, next));
		next.x += step.x;
		next.y += step.y;
	}
	return (INFINITY);
}
