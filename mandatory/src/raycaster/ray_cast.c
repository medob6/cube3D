/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbousset <mbousset@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 15:39:30 by mbousset          #+#    #+#             */
/*   Updated: 2025/07/01 21:10:52 by mbousset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycaster.h"

#define WALL_HIGHT 100

double	teranry(bool cond, double a, double b)
{
	if (cond)
		return (a);
	return (b);
}

int	is_oob(t_point tile)
{
	t_game	*g;

	g = get_game();
	if (tile.x < 0 || tile.y < 0)
		return (1);
	if (tile.x >= g->win_w / TILE_SIZE)
		return (1);
	if (tile.y >= g->win_h / TILE_SIZE)
		return (1);
	return (0);
}

double	get_ray_angle(int ray, t_raycaster caster)
{
	return (caster.start_angle + ray * caster.angle_step);
}
static double	verti_dist(double ray_ang, double *wall_x, int *dir)
{
	t_game	*game;
	t_point	h_intersection;
	char	cell;
	int		facing_right;
	int		map_y;
	int		map_x;
	double	next_x;
	double	next_y;

	int x_step, y_step;
	facing_right = ray_ang < M_PI_2 && ray_ang > 3 * M_PI_2;
	game = get_game();
	h_intersection.x = floor(game->player.p.x / TILE_SIZE) * TILE_SIZE;
	h_intersection.x += facing_right ? -0.0001 : TILE_SIZE;
	h_intersection.y = game->player.p.y + ((h_intersection.x - game->player.p.x)
			* tan(ray_ang));
	y_step = TILE_SIZE * (facing_right ? -1 : 1);
	x_step = y_step * tan(ray_ang);
	next_x = h_intersection.x;
	next_y = h_intersection.y;
	while (true)
	{
		map_y = (int)(next_y / TILE_SIZE);
		map_x = (int)(next_x / TILE_SIZE);
		if (map_y < 0 || map_y >= game->win_h / TILE_SIZE || map_x < 0
			|| map_x >= game->win_w / TILE_SIZE)
			break ;
		cell = game->data.map.arr[map_y][map_x];
		if (cell == '1')
		{
			if (facing_right)
				*wall_x = fmod(next_y, TILE_SIZE);
			else
				*wall_x = TILE_SIZE - fmod(next_y, TILE_SIZE);
			*dir = facing_right ? E_WALL : W_WALL;
			return (hypot(next_x - game->player.p.x, next_y
					- game->player.p.y));
		}
		else if (cell == ' ')
			break ;
		next_y += y_step;
		next_x += x_step;
	}
	return (INFINITY);
}

static double	horiz_dist(double ray_ang, double *wall_x, int *dir)
{
	t_game	*game;
	t_point	v_intersection;
	char	cell;
	int		facing_up;
	int		map_y;
	int		map_x;
	double	next_x;
	double	next_y;

	int x_step, y_step;
	facing_up = ray_ang < M_PI;
	game = get_game();
	v_intersection.y = floor(game->player.p.y / TILE_SIZE) * TILE_SIZE;
	v_intersection.y += facing_up ? -0.0001 : TILE_SIZE;
	v_intersection.x = game->player.p.x + ((v_intersection.y - game->player.p.y)
			/ tan(ray_ang));
	y_step = TILE_SIZE * (facing_up ? -1 : 1);
	x_step = y_step / tan(ray_ang);
	next_x = v_intersection.x;
	next_y = v_intersection.y;
	while (true)
	{
		map_y = (int)(next_y / TILE_SIZE);
		map_x = (int)(next_x / TILE_SIZE);
		if (map_y < 0 || map_y >= game->win_h / TILE_SIZE || map_x < 0
			|| map_x >= game->win_w / TILE_SIZE)
			break ;
		cell = game->data.map.arr[map_y][map_x];
		if (cell == ' ')
			break ;
		if (cell == '1')
		{
			if (facing_up)
				*wall_x = fmod(next_x, TILE_SIZE);
			else
				*wall_x = TILE_SIZE - fmod(next_x, TILE_SIZE);
			*dir = teranry(facing_up, N_WALL, S_WALL);
			return (hypot(next_x - game->player.p.x, next_y
					- game->player.p.y));
		}
		next_y += y_step;
		next_x += x_step;
	}
	return (INFINITY);
}

double	closest_hit(double ang, double *wall_x, int *dir)
{
	double	h;
	double	v;
	double	h_x;
	double	v_x;
	t_game	*g;

	g = get_game();
	h = horiz_dist(ang, &h_x, dir);
	v = verti_dist(ang, &v_x, dir);
	if (h < v)
	{
		*wall_x = h_x;
		return (h * cos(ang - g->player.angle));
	}
	*wall_x = v_x;
	return (v * cos(ang - g->player.angle));
}

void	init_raycaster(t_raycaster *c)
{
	t_game	*g;

	g = get_game();
	c->num_rays = g->win_w;
	c->angle_step = FOV_ANGLE / c->num_rays;
	c->distances = malloc(sizeof(double) * c->num_rays);
}

unsigned int	get_slice_color(int x, int y, int dir, int section)
{
	if (section == 1)
		return (get_game()->data.ceiling_clr);
	else if (section == 2)
	{
		if ((x >= 0 && x <= get_game()->win_w) && (y >= 0
				&& y <= get_game()->win_h))
			return (get_color(get_game()->graphics[dir], x, y));
	}
	else if (section == 3)
		return (get_game()->data.ceiling_clr);
	return (0);
}

void	draw_section(int start, int end, int num, t_sec_inf *section)
{
	int	i;
	int	tex_x;
	int	tex_y;

	int d_from_top, color;
	i = start;
	while (i <= end)
	{
		if (num == 2)
		{
			d_from_top = i - start;
			tex_y = (int)((double)d_from_top / section->wall_h * get_game()->graphics[section->wall].h);
			tex_x = section->wall_x / TILE_SIZE * get_game()->graphics[section->wall].w;
		}
		color = get_slice_color((int)tex_x, (int)tex_y, section->wall, num);
		my_mlx_pixel_put(get_game()->display, section->win_x, i, color);
		i++;
	}
}

t_sec_inf	*init_section(int w_x, double wall_h, int x, int dir)
{
	t_sec_inf	*section;

	section = malloc(sizeof(t_sec_inf));
	section->wall_h = wall_h;
	section->wall = dir;
	section->wall_x = x;
	section->win_x = w_x;
	return (section);
}

void	draw_wall_slice(int w_x, double wall_h, int x, int dir)
{
	int			wall_top;
	t_sec_inf	*section;
	int			wall_bottom;

	wall_top = get_game()->win_h / 2 - wall_h / 2;
	wall_bottom = wall_top + wall_h;
	section = init_section(w_x, wall_h, x, dir);
	draw_section(0, wall_top, 1, section);
	draw_section(wall_top, wall_bottom, 2, section);
	draw_section(wall_bottom, get_game()->win_h, 3, section);
}

void	draw_3d_view(t_game *g, t_raycaster *c)
{
	int		i;
	double	ray_ang;
	double	proj_dist;
	double	proj_wall;
	double	wall_x;
	int		dir;

	c->start_angle = g->player.angle - FOV_ANGLE / 2;
	proj_dist = (g->win_w / 2) / tan(FOV_ANGLE / 2);
	i = -1;
	while (++i < c->num_rays)
	{
		ray_ang = c->start_angle + i * c->angle_step;
		c->distances[i] = closest_hit(ray_ang, &wall_x, &dir);
		proj_wall = (20 / c->distances[i]) * proj_dist;
		draw_wall_slice(i, proj_wall, wall_x, dir);
	}
}

void	cast_rays(t_game *game)
{
	t_raycaster	caster;

	init_raycaster(&caster);
	draw_3d_view(game, &caster);
	free(caster.distances);
}
