/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbousset <mbousset@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 16:07:13 by mbousset          #+#    #+#             */
/*   Updated: 2025/09/08 14:15:30 by mbousset         ###   ########.fr       */
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

	vertical = (map.arr[row - 1][col] == '1' || map.arr[row + 1][col] == '1');
	horizontal = (map.arr[row][col - 1] == '1' || map.arr[row][col + 1] == '1');
	if (vertical)
		return (f.x > WALL_WIDTH / 3 && f.x < WALL_WIDTH * 2 / 3);
	if (horizontal)
		return (f.y > WALL_WIDTH / 3 && f.y < WALL_WIDTH * 2 / 3);
	return (false);
}

static t_point	calc_world_point(t_game *g, double rx, double ry, t_mm_scale sc)
{
	t_point	delta;
	t_point	wp;

	delta.x = -rx * sin(g->player.angle) - ry * cos(g->player.angle);
	delta.y = rx * cos(g->player.angle) - ry * sin(g->player.angle);
	wp.x = g->player.p.x + delta.x / sc.world_zoom;
	wp.y = g->player.p.y + delta.y / sc.world_zoom;
	return (wp);
}

static int	get_out_of_bounds_color(t_game *g, int row, int col)
{
	if (row < 0 || row >= g->data.map.map_h || col < 0
		|| col >= g->data.map.map_w)
		return (0x000000);
	return (-1);
}

static int	get_door_color(t_point f, int row, int col, char type)
{
	t_game	*g;

	g = get_game();
	if (in_door(f, g->data.map, row, col))
	{
		if (get_door(col, row).frame != 9)
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

static int	get_tile_color(t_point wp, int row, int col, t_mm_scale sc)
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
