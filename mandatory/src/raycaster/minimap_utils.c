/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbousset <mbousset@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 16:07:13 by mbousset          #+#    #+#             */
/*   Updated: 2025/07/14 09:44:55 by mbousset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

t_mm_scale	get_minimap_scale(t_game *g, double radius)
{
	const int	shortest = fmin(g->win_w, g->win_h);
	t_mm_scale	sc;
	double		world_units_visible;

	world_units_visible = shortest * (1.0 / 3.0);
	sc.world_zoom = radius / world_units_visible;
	sc.px_border = fmin(fmax(radius * 0.01, 1.0), 6.0);
	return (sc);
}

bool	in_border(t_point f, t_mm_scale sc)
{
	if (f.x < sc.px_border || f.x > WALL_WIDTH - sc.px_border
		|| f.y < sc.px_border || f.y > WALL_WIDTH - sc.px_border)
		return (true);
	return (false);
}

int	get_minimap_pixel_color(t_game *g, double rx, double ry, t_mm_scale sc)
{
	t_point	delta;
	t_point	wp;
	t_point	f;
	int		row;
	int		col;

	delta.x = -rx * sin(g->player.angle) - ry * cos(g->player.angle);
	delta.y = rx * cos(g->player.angle) - ry * sin(g->player.angle);
	wp.x = g->player.p.x + delta.x / sc.world_zoom;
	wp.y = g->player.p.y + delta.y / sc.world_zoom;
	col = wp.x / WALL_WIDTH;
	row = wp.y / WALL_WIDTH;
	if (row < 0 || row >= g->data.map.map_h || col < 0
		|| col >= g->data.map.map_w)
		return (0x000000);
	if (g->data.map.arr[row][col] == '0'
		|| is_valid_dir(g->data.map.arr[row][col]))
		return (0xeeeeee);
	else if (g->data.map.arr[row][col] == ' ')
		return (0x000000);
	f.x = fmod(wp.x, WALL_WIDTH);
	f.y = fmod(wp.y, WALL_WIDTH);
	if (in_border(f, sc))
		return (0x000000);
	return (0x633974);
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
