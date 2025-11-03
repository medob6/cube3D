/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster_init.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbousset <mbousset@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 09:26:46 by mbousset          #+#    #+#             */
/*   Updated: 2025/09/16 09:26:49 by mbousset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycaster_bs.h"

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

int	get_direction(int up)
{
	if (up)
		return (-1);
	return (1);
}

bool	is_valid_door_position(int px, int py, t_rayinfo *ray)
{
	t_game	*g;

	g = get_game();
	return (px > 0 && px < g->data.map.map_w - 1 && py >= 0
		&& py < g->data.map.map_h && ft_strchr("DX", g->data.map.arr[py][px])
		&& g->data.map.arr[py][px + 1] == '1' && g->data.map.arr[py][px
		- 1] == '1' && ((fmod(g->player.p.y, WALL_WIDTH) <= WALL_WIDTH
				/ 2) ^ ray->up));
}
