/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbousset <mbousset@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 15:39:30 by mbousset          #+#    #+#             */
/*   Updated: 2025/07/10 19:04:24 by mbousset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycaster.h"

#define WALL_HIGHT 64

double	get_ray_angle(int ray, t_raycaster caster)
{
	return (caster.start_angle + ray * caster.angle_step);
}

static double	verti_dist(double ray_ang, double *wall_x, int *dir)
{
	t_game	*game;
	t_point	v_intersection;
	bool	facing_left;
	double	x_step;
	double	y_step;

	game = get_game();
	facing_left = cos(ray_ang) < 0;
	double next_x, next_y;
	int map_x, map_y;
	x_step = TILE_SIZE * (facing_left ? -1 : 1);
	y_step = x_step * tan(ray_ang);
	v_intersection.x = floor(game->player.p.x / TILE_SIZE) * TILE_SIZE;
	if (!facing_left)
		v_intersection.x += TILE_SIZE;
	v_intersection.y = game->player.p.y + (v_intersection.x - game->player.p.x)
		* tan(ray_ang);
	next_x = v_intersection.x;
	next_y = v_intersection.y;
	while (true)
	{
		map_x = (int)((facing_left ? next_x - 1 : next_x) / TILE_SIZE);
		map_y = (int)(next_y / TILE_SIZE);
		if (map_x < 0 || map_x >= game->data.map.map_w || map_y < 0
			|| map_y >= game->data.map.map_h)
			break ;
		if (game->data.map.arr[map_y][map_x] == '1')
		{
			*wall_x = next_y;
			*dir = facing_left ? W_WALL : E_WALL;
			return (hypot(next_x - game->player.p.x, next_y
					- game->player.p.y));
		}
		next_x += x_step;
		next_y += y_step;
	}
	return (INFINITY);
}

static double	horiz_dist(double ray_ang, double *wall_x, int *dir)
{
	t_game	*game;
	t_point	h_intersection;
	bool	facing_up;

	game = get_game();
	facing_up = sin(ray_ang) < 0;
	double next_x, next_y;
	double x_step, y_step;
	int map_x, map_y;
	y_step = TILE_SIZE * (facing_up ? -1 : 1);
	x_step = y_step / tan(ray_ang);
	h_intersection.y = floor(game->player.p.y / TILE_SIZE) * TILE_SIZE;
	if (!facing_up)
		h_intersection.y += TILE_SIZE;
	h_intersection.x = game->player.p.x + (h_intersection.y - game->player.p.y)
		/ tan(ray_ang);
	next_x = h_intersection.x;
	next_y = h_intersection.y;
	while (true)
	{
		map_x = (int)(next_x / TILE_SIZE);
		map_y = (int)((facing_up ? next_y - 1 : next_y) / TILE_SIZE);
		if (map_x < 0 || map_x >= game->data.map.map_w || map_y < 0
			|| map_y >= game->data.map.map_h)
			break ;
		if (game->data.map.arr[map_y][map_x] == '1')
		{
			*wall_x = next_x;
			*dir = facing_up ? N_WALL : S_WALL;
			return (hypot(next_x - game->player.p.x, next_y
					- game->player.p.y));
		}
		next_x += x_step;
		next_y += y_step;
	}
	return (INFINITY);
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
	return (0xffffff);
}

void	draw_section(int start, int end, int num, t_sec_inf *section)
{
	int		i;
	t_image	tex;
	double	d_from_top;
	int		color;

	int tex_x, tex_y;
	i = start;
	if (section->sec.dir != -1)
		tex = get_game()->graphics[section->sec.dir];
	while (i <= end)
	{
		if (num == 2 && section->sec.dir != -1)
		{
			d_from_top = i - start + section->tex_offset;
			tex_y = (d_from_top / section->sec.wall_h) * tex.h;
			tex_x = fmod(section->sec.wall_x, TILE_SIZE) / TILE_SIZE * tex.w;
		}
		color = get_slice_color(tex_x, tex_y, section->sec.dir, num);
		my_mlx_pixel_put(get_game()->display, section->win_x, i, color);
		i++;
	}
}

t_sec_inf	*init_section(int w_x, double wall_h, int x, t_graphic dir)
{
	t_sec_inf	*section;

	section = malloc(sizeof(t_sec_inf));
	section->sec.wall_h = wall_h;
	section->sec.dir = dir;
	section->sec.wall_x = x;
	section->win_x = w_x;
	section->tex_offset = 0;
	return (section);
}

bool	in_minimap_range(int w_x)
{
	int	minimap_r;
	int	minima_c;
	int	var;

	minimap_r = get_game()->win_h * MINIMAP_SCREEN_SCALE;
	minima_c = minimap_r * 1.2;
	var = minimap_r + minimap_r * ICON_SCALE;
	if (w_x < minima_c + var && w_x > minima_c - var)
		return (true);
	return (false);
}

void	draw_wall_slice(int w_x, t_sec *slice, int old_wh)
{
	int			wall_top;
	t_sec_inf	*section;
	int			wall_bottom;
	int			old_wt;
	int			old_wb;

	old_wt = (get_game()->win_h / 2 - old_wh / 2) * (old_wh != 0)
		+ get_game()->player.p.z - 1;
	old_wb = old_wt + old_wh;
	if (old_wh == 0 || in_minimap_range(w_x))
		old_wb = get_game()->win_h;
	section = init_section(w_x, slice[w_x].wall_h, slice[w_x].wall_x,slice[w_x].dir);
	wall_top = get_game()->win_h / 2 - slice[w_x].wall_h / 2
		+ get_game()->player.p.z;
	wall_bottom = wall_top + slice[w_x].wall_h;
	if (wall_top < 0)
	{
		section->tex_offset = -wall_top;
		wall_top = 0;
	}
	if (wall_bottom > get_game()->win_h)
		wall_bottom = get_game()->win_h;
	if (old_wt < 0)
		old_wt = 0;
	if (old_wt < wall_top)
		draw_section(old_wt, wall_top, 1, section);
	draw_section(wall_top, wall_bottom, 2, section);
	if (wall_bottom < old_wb)
		draw_section(wall_bottom, old_wb, 3, section);
	free(section);
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

bool	check_in_range(int ray, int offset, int max_rays)
{
	if (offset > 0)
	{
		if (ray < max_rays - offset)
			return (true);
	}
	else if (offset < 0)
	{
		if (ray >= -offset)
			return (true);
	}
	return (false);
}

static inline void	swap_buffers(t_raycaster *c)
{
	t_sec	*tmp;

	tmp = c->prev_lines;
	c->prev_lines = c->lines;
	c->lines = tmp;
}

double	closest_hit(double ang, t_sec *line)
{
	t_game	*g;
	double	raw_dist;

	double h, v;
	double h_x, v_x;
	int h_dir, v_dir;
	h_dir = -1;
	v_dir = -1;
	g = get_game();
	h = horiz_dist(ang, &h_x, &h_dir);
	v = verti_dist(ang, &v_x, &v_dir);
	if (h < v)
	{
		line->dir = h_dir;
		line->wall_x = h_x;
		raw_dist = h;
	}
	else
	{
		line->dir = v_dir;
		line->wall_x = v_x;
		raw_dist = v;
	}
	line->raw_dist = raw_dist;
	return (raw_dist * cos(normalize_angle(ang - g->player.angle)));
}

void	draw_3d_view(t_game *g, t_raycaster *c)
{
	int		i;
	double	ray_ang;
	double	proj_dist;
	bool	pos_changed;
	int		ray_offset;
	double	old_ang;
	double	d;
	double	corrected_dist;
	double	old_wh;

	ray_offset = 0;
	pos_changed = check_position(g);
	old_ang = get_old_angel(g);
	if (old_ang != g->player.angle)
		ray_offset = (g->player.angle - old_ang) / c->angle_step;
	c->start_angle = g->player.angle - FOV_ANGLE / 2;
	proj_dist = (g->win_w / 2) / tan(FOV_ANGLE / 2);
	i = -1;
	while (++i < c->num_rays)
	{
		old_wh = c->prev_lines[i].wall_h;
		ray_ang = normalize_angle(c->start_angle + i * c->angle_step);
		if (!pos_changed && check_in_range(i, ray_offset, c->num_rays))
		{
			c->lines[i] = c->prev_lines[i + ray_offset];
			corrected_dist = c->lines[i].raw_dist * cos(normalize_angle(ray_ang
						- g->player.angle));
			c->lines[i].wall_h = (WALL_HIGHT / corrected_dist) * proj_dist;
		}
		else
		{
			d = closest_hit(ray_ang, &c->lines[i]);
			c->lines[i].wall_h = (WALL_HIGHT / d) * proj_dist;
		}
		draw_wall_slice(i, c->lines, old_wh);
	}
	swap_buffers(c);
}

void	init_raycaster(t_raycaster *c)
{
	t_game	*g;

	g = get_game();
	c->num_rays = g->win_w;
	c->angle_step = FOV_ANGLE / c->num_rays;
	c->lines = malloc(sizeof(t_sec) * c->num_rays);
	c->prev_lines = malloc(sizeof(t_sec) * c->num_rays);
}
void	cast_rays(t_game *game)
{
	static bool			first = true;
	static t_raycaster	caster;

	if (first)
	{
		init_raycaster(&caster);
		first = false;
	}
	draw_3d_view(game, &caster);
}
