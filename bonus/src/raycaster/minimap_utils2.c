/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbousset <mbousset@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 08:59:39 by mbousset          #+#    #+#             */
/*   Updated: 2025/09/16 09:01:26 by mbousset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_bs.h"

t_mm_scale	get_minimap_scale(t_game *g, double radius)
{
	const int	shortest = fmin(g->win_w, g->win_h);
	t_mm_scale	sc;
	double		world_units_visible;

	world_units_visible = shortest * WORLD_VISIBILITY_UNIT_FACTOR;
	sc.world_zoom = radius / world_units_visible;
	sc.px_border = fmin(fmax(radius * 0.5, 1.0), 6.0);
	return (sc);
}

bool	in_border(t_point f, t_mm_scale sc)
{
	if (f.x < sc.px_border || f.x > WALL_WIDTH - sc.px_border
		|| f.y < sc.px_border || f.y > WALL_WIDTH - sc.px_border)
		return (true);
	return (false);
}

bool	in_door(t_point f, t_map map, int row, int col)
{
	bool	vertical;
	bool	horizontal;

	vertical = (map.arr[row - 1][col] == '1' && map.arr[row + 1][col] == '1');
	horizontal = (map.arr[row][col - 1] == '1' && map.arr[row][col + 1] == '1');
	if (vertical)
		return (f.x > WALL_WIDTH / 3 && f.x < WALL_WIDTH * 2 / 3);
	if (horizontal)
		return (f.y > WALL_WIDTH / 3 && f.y < WALL_WIDTH * 2 / 3);
	return (false);
}

t_point	calc_world_point(t_game *g, double rx, double ry, t_mm_scale sc)
{
	t_point	delta;
	t_point	wp;

	delta.x = -rx * sin(g->player.angle) - ry * cos(g->player.angle);
	delta.y = rx * cos(g->player.angle) - ry * sin(g->player.angle);
	wp.x = g->player.p.x + delta.x / sc.world_zoom;
	wp.y = g->player.p.y + delta.y / sc.world_zoom;
	return (wp);
}

int	get_out_of_bounds_color(t_game *g, int row, int col)
{
	if (row < 0 || row >= g->data.map.map_h || col < 0
		|| col >= g->data.map.map_w)
		return (0x000000);
	return (-1);
}
