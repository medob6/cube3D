/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_toward_door.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbousset <mbousset@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 09:03:16 by mbousset          #+#    #+#             */
/*   Updated: 2025/09/16 09:09:23 by mbousset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_bs.h"

bool	is_door_fully_open(double new_x, double new_y, char cell)
{
	if (get_door((int)(new_x / WALL_WIDTH), (int)(new_y
		/ WALL_WIDTH)).frame == get_game()->graphics[DOOR].frames - 1)
		return (cell == 'D');
	return (false);
}

bool	is_vertical_door_aligned(double new_x)
{
	double	offset;

	offset = fmod(new_x, WALL_WIDTH);
	return (offset < (WALL_WIDTH / 2.0 - WALL_WIDTH * 0.1)
		|| offset > (WALL_WIDTH / 2.0 + WALL_WIDTH * 0.1));
}

bool	is_horizontal_door_aligned(double new_y)
{
	double	offset;

	offset = fmod(new_y, WALL_WIDTH);
	return (offset < (WALL_WIDTH / 2.0 - WALL_WIDTH * 0.1)
		|| offset > (WALL_WIDTH / 2.0 + WALL_WIDTH * 0.1));
}

bool	is_door_passable(double new_x, double new_y, char **map, char cell)
{
	char	u_cell;
	char	d_cell;
	char	l_cell;
	char	r_cell;
	t_point	p;

	p.x = (int)(new_x / WALL_WIDTH);
	p.y = (int)(new_y / WALL_WIDTH);
	u_cell = map[(int)p.y + 1][(int)p.x];
	d_cell = map[(int)p.y - 1][(int)p.x];
	l_cell = map[(int)p.y][(int)p.x + 1];
	r_cell = map[(int)p.y][(int)p.x - 1];
	if (ft_strchr("DX", cell))
	{
		if (u_cell == '1' && d_cell == '1')
			return (is_vertical_door_aligned(new_x));
		else if (r_cell == '1' && l_cell == '1')
			return (is_horizontal_door_aligned(new_y));
	}
	return (false);
}

bool	valid_door_pos(double new_x, double new_y)
{
	char	**map;
	char	cell;
	int		x;
	int		y;

	map = get_game()->data.map.arr;
	x = (int)(new_x / WALL_WIDTH);
	y = (int)(new_y / WALL_WIDTH);
	cell = map[y][x];
	if (is_door_fully_open(new_x, new_y, cell))
		return (true);
	if (is_door_passable(new_x, new_y, map, cell))
		return (true);
	if (cell == 'X' && get_door(x, y).frame == get_game()->graphics[DOOR].frames
		- 1)
		get_game()->passed = true;
	return (false);
}
