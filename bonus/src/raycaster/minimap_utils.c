/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbousset <mbousset@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 16:07:13 by mbousset          #+#    #+#             */
/*   Updated: 2025/09/16 09:00:14 by mbousset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_bs.h"

int	get_door_color(t_point f, int row, int col, char type)
{
	t_game	*g;

	g = get_game();
	if (in_door(f, g->data.map, row, col))
	{
		if (get_door(col, row).frame != get_game()->graphics[DOOR].frames - 1)
		{
			if (type == 'D')
				return (0xff0000);
			if (type == 'X')
				return (0xFFD700);
		}
		return (0x00ff00);
	}
	return (0xffffff);
}

int	get_tile_color(t_point wp, int row, int col, t_mm_scale sc)
{
	t_game	*g;
	t_point	f;

	g = get_game();
	if (g->data.map.arr[row][col] == '0'
		|| is_valid_dir(g->data.map.arr[row][col]))
		return (0xeeeeee);
	else if (g->data.map.arr[row][col] == ' ')
		return (0x000000);
	else if (g->data.map.arr[row][col] == 'D'
		|| g->data.map.arr[row][col] == 'X')
	{
		f.x = fmod(wp.x, WALL_WIDTH);
		f.y = fmod(wp.y, WALL_WIDTH);
		return (get_door_color(f, row, col, g->data.map.arr[row][col]));
	}
	else
	{
		f.x = fmod(wp.x, WALL_WIDTH);
		f.y = fmod(wp.y, WALL_WIDTH);
		if (in_border(f, sc))
			return (0x000000);
		return (0x633974);
	}
}

int	get_minimap_pixel_color(t_game *g, double rx, double ry, t_mm_scale sc)
{
	t_point	wp;
	int		row;
	int		col;
	int		c;

	wp = calc_world_point(g, rx, ry, sc);
	col = wp.x / WALL_WIDTH;
	row = wp.y / WALL_WIDTH;
	c = get_out_of_bounds_color(g, row, col);
	if (c != -1)
		return (c);
	return (get_tile_color(wp, row, col, sc));
}

int	get_icone_color(t_graphic icone, double raidus, double x, double y)
{
	double	img_x;
	double	img_y;
	t_game	*game;

	game = get_game();
	img_x = (x + raidus) * game->graphics[icone].w / (raidus * 2);
	img_y = (y + raidus) * game->graphics[icone].w / (raidus * 2);
	return (get_color(game->graphics[icone], img_x, img_y));
}

void	get_icone_info(t_circle *icn, t_circle minimap, double icon_angle,
		double player_angle)
{
	double	delta;

	delta = normalize_angle(icon_angle - player_angle + M_PI_2);
	icn->radius = minimap.radius * ICON_SCALE;
	icn->c.x = cos(delta) * minimap.radius * 0.99 + minimap.c.x;
	icn->c.y = sin(delta) * minimap.radius * 0.99 + minimap.c.y;
}
