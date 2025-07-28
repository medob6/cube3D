/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   horizontal_raycast.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbousset <mbousset@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 15:50:02 by mbousset          #+#    #+#             */
/*   Updated: 2025/07/12 18:51:29 by mbousset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycaster.h"

void	init_raycaster(t_raycaster *c)
{
	t_game	*g;

	g = get_game();
	c->num_rays = g->win_w;
	c->angle_step = FOV_ANGLE / c->num_rays;
	c->lines = ft_calloc(c->num_rays, sizeof(t_sec));
	c->prev_lines = ft_calloc(c->num_rays, sizeof(t_sec));
}

void	get_h_inter(t_point *next, bool facing_up, double ray_ang)
{
	next->y = floor(get_game()->player.p.y / WALL_WIDTH) * WALL_WIDTH;
	if (!facing_up)
		next->y += WALL_WIDTH;
	next->x = get_game()->player.p.x + (next->y - get_game()->player.p.y)
		/ tan(ray_ang);
}

void	get_steps_h(t_pair *step, bool up, double ray_ang)
{
	step->y = WALL_WIDTH * (-up + !up);
	step->x = step->y / tan(ray_ang);
}

double	horiz_dist(double ray_ang, double *wall_x, int *dir)
{
	t_point			map_p;
	t_point			next;
	t_pair			step;
	bool			up;
	const t_game	*g = get_game();

	up = sin(ray_ang) < 0;
	get_h_inter(&next, up, ray_ang);
	get_steps_h(&step, up, ray_ang);
	while (true)
	{
		map_p.x = next.x / WALL_WIDTH;
		map_p.y = ((next.y - 1) * (up) + next.y * (!up)) / WALL_WIDTH;
		if (outside_map(map_p.x, map_p.y))
			break ;
		if (g->data.map.arr[(int)map_p.y][(int)map_p.x] == '1')
			return (*wall_x = next.x, *dir = N_WALL * up + S_WALL * !up,
				get_dist(g->player.p, next));
		next.x += step.x;
		next.y += step.y;
	}
	return (INFINITY);
}
