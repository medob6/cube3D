/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbousset <mbousset@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 09:02:20 by mbousset          #+#    #+#             */
/*   Updated: 2025/07/12 10:53:25 by mbousset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static t_mm_scale	get_minimap_scale(t_game *g, double radius)
{
	const int	shortest = fmin(g->win_w, g->win_h);
	t_mm_scale	sc;
	double		world_units_visible;

	world_units_visible = shortest / 3.0;
	sc.world_zoom = (radius * 1.4) / world_units_visible;
	sc.px_border = fmin(fmax(radius * 0.01, 1.0), 6.0);
	return (sc);
}

bool	in_border(t_point f, t_mm_scale sc)
{
	if (f.x < sc.px_border || f.x > TILE_SIZE * UNITE - sc.px_border
		|| f.y < sc.px_border || f.y > TILE_SIZE * UNITE - sc.px_border)
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
	col = wp.x / TILE_SIZE * UNITE;
	row = wp.y / TILE_SIZE * UNITE;
	if (row < 0 || row >= g->data.map.map_h || col < 0
		|| col >= g->data.map.map_w)
		return (0x000000);
	if (g->data.map.arr[row][col] == '0'
		|| is_valid_dir(g->data.map.arr[row][col]))
		return (0xeeeeee);
	else if (g->data.map.arr[row][col] == ' ')
		return (0x000000);
	f.x = fmod(wp.x, TILE_SIZE * UNITE);
	f.y = fmod(wp.y, TILE_SIZE * UNITE);
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

void	put_icon_on_edeg(t_graphic icone, t_circle minimap, double icon_angle)
{
	t_game		*game;
	t_circle	icn;
	t_point		p;
	int			color;

	game = get_game();
	get_icone_info(&icn, minimap, icon_angle, game->player.angle);
	p.y = -icn.radius;
	while (p.y < icn.radius)
	{
		p.x = -icn.radius;
		while (p.x < icn.radius)
		{
			color = get_icone_color(icone, icn.radius, p.x, p.y);
			if (pow_2(p.x) + pow_2(p.y) <= pow_2(icn.radius))
				my_mlx_pixel_put(game->display, icn.c.x + p.x, icn.c.y + p.y,
					color);
			p.x++;
		}
		p.y++;
	}
}

void	draw_player(t_game *game, t_circle minimap)
{
	double	scale;
	int		color;
	t_point	src;
	t_point	p;
	t_point	n;

	scale = minimap.radius * PLAYER_SCALE;
	n.x = -1;
	while (++n.x < scale)
	{
		n.y = -1;
		while (++n.y < scale)
		{
			src.x = (int)((double)n.x / scale * game->graphics[ARROW].w);
			src.y = (int)((double)n.y / scale * game->graphics[ARROW].h);
			color = get_color(game->graphics[ARROW], src.x, src.y);
			if (get_t(color) != 255)
			{
				p.x = minimap.c.x + n.x - scale / 2;
				p.y = minimap.c.y + n.y - scale / 2;
				my_mlx_pixel_put(game->display, p.x, p.y, color);
			}
		}
	}
}

int	get_minimap_color(t_point p, double m_radius, t_mm_scale sc)
{
	t_game	*game;
	int		color;

	game = get_game();
	color = get_minimap_pixel_color(game, p.x, p.y, sc);
	if (pow_2(p.x) + pow_2(p.y) > pow_2(m_radius * 0.94))
		color = 0xffffff;
	if (pow_2(p.x) + pow_2(p.y) > pow_2(m_radius * 0.94) && (pow_2(p.x)
			+ pow_2(p.y) < pow_2(m_radius * 0.96) || pow_2(p.x)
			+ pow_2(p.y) > pow_2(m_radius * 0.99)))
		color = 0xe866bb;
	return (color);
}

void	draw_mini_map(t_game *game)
{
	t_circle	mini_map;
	t_point		p;
	int			color;
	t_mm_scale	sc;

	mini_map.radius = game->win_h * MINIMAP_SCREEN_SCALE;
	mini_map.c.x = mini_map.radius * 1.2;
	mini_map.c.y = game->win_h - mini_map.radius * 1.2;
	sc = get_minimap_scale(game, mini_map.radius);
	p.y = -mini_map.radius - 1;
	while (++p.y < mini_map.radius)
	{
		p.x = -mini_map.radius - 1;
		while (++p.x < mini_map.radius)
		{
			color = get_minimap_color(p, mini_map.radius, sc);
			if (pow_2(p.x) + pow_2(p.y) <= pow_2(mini_map.radius))
				my_mlx_pixel_put(game->display, mini_map.c.x + p.x, mini_map.c.y
					+ p.y, color);
		}
	}
	put_icon_on_edeg(N_ICONE, mini_map, deg_to_rad(90));
	draw_player(game, mini_map);
}
