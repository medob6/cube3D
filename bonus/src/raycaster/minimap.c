/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbousset <mbousset@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 09:02:20 by mbousset          #+#    #+#             */
/*   Updated: 2025/09/07 15:59:44 by mbousset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_bs.h"

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
	double		icon_angle;

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
