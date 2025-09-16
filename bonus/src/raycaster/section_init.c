/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   section_init.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbousset <mbousset@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 09:46:26 by mbousset          #+#    #+#             */
/*   Updated: 2025/09/16 09:47:10 by mbousset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycaster_bs.h"

t_sec_inf	*init_section(int w_x, t_sec_params p)
{
	t_sec_inf	*section;

	section = malloc(sizeof(t_sec_inf));
	if (!section)
		return (NULL);
	section->sec.wall_h = p.wall_h;
	section->sec.wall_x = p.wall_x;
	section->sec.dir = p.dir;
	section->sec.door = p.door;
	section->sec.n = -1;
	section->win_x = w_x;
	section->tex_offset = 0;
	return (section);
}

unsigned int	get_slice_color(int x, int y, int dir, int section)
{
	if (section == 1)
		return (get_game()->data.ceiling_clr);
	else if (section == 2)
	{
		if (dir == -1)
			return (0x000000);
		if ((x >= 0 && x < get_game()->graphics[dir].w) && (y >= 0
				&& y < get_game()->graphics[dir].h))
			return (get_color(get_game()->graphics[dir], x, y));
	}
	else if (section == 3)
		return (get_game()->data.floor_clr);
	return (0x00000);
}

int	apply_shading(int color, double dist)
{
	double	attenuation;
	double	intensity;
	int		r;
	int		g;
	int		b;

	attenuation = 0.0012;
	intensity = 1.0 / (1.0 + dist * attenuation);
	if (intensity < 0.2)
		intensity = 0.2;
	r = ((color >> 16) & 0xFF) * intensity;
	g = ((color >> 8) & 0xFF) * intensity;
	b = (color & 0xFF) * intensity;
	return ((r << 16) | (g << 8) | b);
}

t_floorcast	init_floorcast(t_sec_inf *section)
{
	t_floorcast	fc;

	fc.game = get_game();
	fc.winw = fc.game->win_w;
	fc.winh = fc.game->win_h;
	fc.floor_tex = fc.game->graphics[FLOOR];
	fc.sky_tex = fc.game->graphics[SKY];
	fc.raydirx0 = cos(fc.game->player.angle - FOV_ANGLE / 2.0);
	fc.raydiry0 = sin(fc.game->player.angle - FOV_ANGLE / 2.0);
	fc.raydirx1 = cos(fc.game->player.angle + FOV_ANGLE / 2.0);
	fc.raydiry1 = sin(fc.game->player.angle + FOV_ANGLE / 2.0);
	fc.eyeheight = 0.5 * fc.winh;
	fc.mid = fc.winh / 2.0 + fc.game->player.p.z;
	fc.win_x = section->win_x;
	return (fc);
}

void	initialize_wall_inf(t_wall_inf *inf, t_sec_inf *section, int start)
{
	t_game	*game;

	game = get_game();
	inf->win_h = game->win_h;
	inf->tex = game->graphics[section->sec.dir];
	if (section->sec.wall_h == 0)
		return ;
	inf->raw_dist = WALL_HIGHT / section->sec.wall_h * ((game->win_w / 2)
			/ tan(FOV_ANGLE / 2));
	inf->h_factor = (double)inf->tex.h / section->sec.wall_h;
	inf->offset = -start + section->tex_offset;
	if (section->sec.dir == DOOR)
		inf->tex_p.x = fmod(section->sec.wall_x, WALL_WIDTH) / WALL_WIDTH
			* (inf->tex.w / 10) + ((inf->tex.w / 10) * section->sec.door.frame);
	else if (section->sec.dir == PORTAL)
		inf->tex_p.x = fmod(section->sec.wall_x, WALL_WIDTH) / WALL_WIDTH
			* (inf->tex.w / 32) + ((inf->tex.w / 32) * game->portal_frame);
	else
		inf->tex_p.x = fmod(section->sec.wall_x, WALL_WIDTH) / WALL_WIDTH
			* inf->tex.w;
}
