/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_color.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbousset <mbousset@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 15:51:51 by mbousset          #+#    #+#             */
/*   Updated: 2025/09/08 15:13:21 by mbousset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycaster_bs.h"

// fixing this part ....

// after split functions into lines

// next refactor vars namining

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

static int	apply_shading(int color, double dist)
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

static t_floorcast	init_floorcast(t_sec_inf *section)
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

static void	initialize_wall_inf(t_wall_inf *inf, t_sec_inf *section, int start)
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

static void	draw_wall(int start, int end, t_sec_inf *section, int num)
{
	t_wall_inf	inf;
	double		d_from_top;
	int			color;
	int			i;

	initialize_wall_inf(&inf, section, start);
	i = start - 1;
	while (++i <= end && i < inf.win_h)
	{
		d_from_top = i + inf.offset;
		inf.tex_p.y = d_from_top * inf.h_factor;
		color = get_slice_color(inf.tex_p.x, inf.tex_p.y, section->sec.dir,
				num);
		color = apply_shading(color, inf.raw_dist);
		if (get_t(color) != 255)
			my_mlx_pixel_put(get_game()->display, section->win_x, i, color);
	}
}

static void	get_world_coords(t_floorcast *fc, double rowDist, double *worldx,
		double *worldy)
{
	double	factor;
	double	raydirx;
	double	raydiry;

	factor = (double)fc->win_x / fc->winw;
	raydirx = fc->raydirx0 + factor * (fc->raydirx1 - fc->raydirx0);
	raydiry = fc->raydiry0 + factor * (fc->raydiry1 - fc->raydiry0);
	*worldx = (fc->game->player.p.x / WALL_WIDTH) + rowDist * raydirx;
	*worldy = (fc->game->player.p.y / WALL_WIDTH) + rowDist * raydiry;
}

int	get_tex_color(t_floorcast *fc, t_point world_p, double rowDist, int num)
{
	int	tx;
	int	ty;
	int	color;

	if (num == 1)
	{
		tx = ((int)(world_p.x * fc->sky_tex.w) % fc->sky_tex.w + fc->sky_tex.w)
			% fc->sky_tex.w;
		ty = ((int)(world_p.y * fc->sky_tex.h) % fc->sky_tex.h + fc->sky_tex.h)
			% fc->sky_tex.h;
		color = get_color(fc->sky_tex, tx, ty);
		color = apply_shading(color, rowDist * 100.0);
	}
	else
	{
		tx = ((int)(world_p.x * fc->floor_tex.w) % fc->floor_tex.w
				+ fc->floor_tex.w) % fc->floor_tex.w;
		ty = ((int)(world_p.y * fc->floor_tex.h) % fc->floor_tex.h
				+ fc->floor_tex.h) % fc->floor_tex.h;
		color = get_color(fc->floor_tex, tx, ty);
		color = apply_shading(color, rowDist * 300.0);
	}
	return (color);
}

static void	draw_floor_ceiling(t_floorcast *fc, int start, int end, int num)
{
	int		y;
	double	p;
	double	rowdist;
	t_point	world_p;
	int		color;

	y = start - 1;
	while (++y <= end && y < fc->winh)
	{
		p = (double)y - fc->mid;
		if (p == 0.0)
			continue ;
		rowdist = fc->eyeheight / fabs(p);
		get_world_coords(fc, rowdist, &world_p.x, &world_p.y);
		color = get_tex_color(fc, world_p, rowdist, num);
		my_mlx_pixel_put(fc->game->display, fc->win_x, y, color);
	}
}

void	draw_section(int start, int end, int num, t_sec_inf *section)
{
	t_floorcast	fc;

	if (num == 2 && section->sec.dir != -1)
	{
		draw_wall(start, end, section, num);
		return ;
	}
	if (num != 1 && num != 3)
		return ;
	fc = init_floorcast(section);
	draw_floor_ceiling(&fc, start, end, num);
}

bool	in_minimap_range(int w_x)
{
	int	minimap_r;
	int	minima_c;
	int	var;

	minimap_r = get_game()->win_h * MINIMAP_SCREEN_SCALE;
	minima_c = minimap_r * 1.2;
	var = minimap_r + minimap_r * ICON_SCALE * 2;
	if (w_x < minima_c + var && w_x > minima_c - var)
		return (true);
	return (false);
}

void	calculate_old_boundaries(int old_wh, int w_x, int *old_wt, int *old_wb)
{
	*old_wt = (get_game()->win_h / 2 - old_wh / 2 + get_game()->player.p.z)
		* (old_wh != 0);
	*old_wb = *old_wt + old_wh;
	if (old_wh == 0 || in_minimap_range(w_x))
		*old_wb = get_game()->win_h;
	if (*old_wt < 0)
		*old_wt = 0;
}
