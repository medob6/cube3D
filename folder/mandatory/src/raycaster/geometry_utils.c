/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   geometry_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbousset <mbousset@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 15:47:40 by mbousset          #+#    #+#             */
/*   Updated: 2025/07/12 15:47:41 by mbousset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycaster.h"

bool	outside_map(int x, int y)
{
	if (x < 0 || x >= get_game()->data.map.map_w || y < 0
		|| y >= get_game()->data.map.map_h)
		return (true);
	return (false);
}

double	get_dist(t_point p, t_point next)
{
	return (hypot(next.x - p.x, next.y - p.y));
}

double	get_ray_angle(int ray, t_raycaster caster)
{
	return (caster.start_angle + ray * caster.angle_step);
}

bool	check_position(t_game *g)
{
	static double	new_x = -1;
	static double	new_y = -1;

	if (new_x == -1)
	{
		new_x = g->player.p.x;
		new_y = g->player.p.y;
		return (true);
	}
	if ((new_x != g->player.p.x || new_y != g->player.p.y))
	{
		new_x = g->player.p.x;
		new_y = g->player.p.y;
		return (true);
	}
	else
		return (false);
}

double	get_old_angel(t_game *g)
{
	static double	old_ang = -1;
	double			tmp;

	if (old_ang == -1)
	{
		old_ang = g->player.angle;
		return (g->player.angle);
	}
	else
	{
		tmp = old_ang;
		old_ang = g->player.angle;
		return (tmp);
	}
}
