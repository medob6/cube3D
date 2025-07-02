/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbousset <mbousset@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 15:39:30 by mbousset          #+#    #+#             */
/*   Updated: 2025/07/02 19:38:39 by mbousset         ###   ########.fr       */
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
			*wall_x = fmod(next_y, TILE_SIZE);
			*dir = facing_left ? W_WALL : E_WALL;
			return (hypot(next_x - game->player.p.x, next_y
					- game->player.p.y));
		}
		next_x += x_step;
		next_y += y_step;
	}
	return (INFINITY);
}

static double horiz_dist(double ray_ang, double *wall_x, int *dir)
{
	t_game	*game = get_game();
	t_point	h_intersection;
	bool	facing_up = sin(ray_ang) < 0;

	double next_x, next_y;
	double x_step, y_step;
	int map_x, map_y;

	y_step = TILE_SIZE * (facing_up ? -1 : 1);
	x_step = y_step / tan(ray_ang);

	// Find first horizontal intersection
	h_intersection.y = floor(game->player.p.y / TILE_SIZE) * TILE_SIZE;
	if (!facing_up)
		h_intersection.y += TILE_SIZE;
	h_intersection.x = game->player.p.x + (h_intersection.y - game->player.p.y) / tan(ray_ang);

	next_x = h_intersection.x;
	next_y = h_intersection.y;

	while (true)
	{
		map_x = (int)(next_x / TILE_SIZE);
		map_y = (int)((facing_up ? next_y - 1 : next_y) / TILE_SIZE);

		if (map_x < 0 || map_x >= game->data.map.map_w || map_y < 0
			|| map_y >= game->data.map.map_h)
			break;

		if (game->data.map.arr[map_y][map_x] == '1')
		{
			*wall_x = fmod(next_x, TILE_SIZE);
			*dir = facing_up ? N_WALL : S_WALL;
			return hypot(next_x - game->player.p.x, next_y - game->player.p.y);
		}

		next_x += x_step;
		next_y += y_step;
	}
	return INFINITY;
}

double	closest_hit(double ang, double *wall_x, int *dir)
{
	t_game	*g;

	double h, v;
	double h_x, v_x;
	int h_dir, v_dir;
	g = get_game();
	h = horiz_dist(ang, &h_x, &h_dir);
	v = verti_dist(ang, &v_x, &v_dir);
	if (h < v)
	{
		*dir = h_dir;
		*wall_x = h_x;
		return (h * cos(normalize_angle(ang - g->player.angle)));
	}
	else
	{
		*dir = v_dir;
		*wall_x = v_x;
		return (v * cos(normalize_angle(ang - g->player.angle)));
	}
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
	{
		// return (get_game()->data.ceiling_clr);
		return (0x87CEEB);
	}
	else if (section == 2)
	{
		// if (dir == N_WALL)
		// 	return (0x000000);
		// else if (dir == S_WALL)
		// 	return (0xffffff);
		// else if (dir == E_WALL)
		// 	return (0xff00ff);
		// else
		// 	return (0x00ff00);
		if ((x >= 0 && x <= get_game()->win_w) && (y >= 0
				&& y <= get_game()->win_h))
			return (get_color(get_game()->graphics[dir], x, y));
	}
	else if (section == 3)
	{
		return (0x8b5a2b);
		// return (get_game()->data.ceiling_clr);
	}
	return (0);
}
void	draw_section(int start, int end, int num, t_sec_inf *section)
{
	int		i;
	t_image	tex;

	int tex_x, tex_y;
	i = start;
	int d_from_top, color;
	tex = get_game()->graphics[section->wall];
	while (i <= end)
	{
		if (num == 2)
		{
			d_from_top = i - start;
			tex_y = fmod(section->wall_x, TILE_SIZE) / TILE_SIZE * tex.w;
			tex_x = (section->wall_x / TILE_SIZE) * tex.w;
			// if (tex_x < 0)
			// 	tex_x = 0;
			// if (tex_x >= tex.w)
			// 	tex_x = tex.w - 1;
			// if (tex_y >= tex.h)
			// 	tex_y = tex.h - 1;
		}
		color = get_slice_color(tex_x, tex_y, section->wall, num);
		my_mlx_pixel_put(get_game()->display, section->win_x, i, color);
		i++;
	}
}

t_sec_inf	*init_section(int w_x, double wall_h, int x, t_graphic dir)
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
	if (wall_top < 0)
		wall_top = 0;
	if (wall_bottom > get_game()->win_h)
		wall_bottom = get_game()->win_h;
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
		ray_ang = normalize_angle(c->start_angle + i * c->angle_step);
		c->distances[i] = closest_hit(ray_ang, &wall_x, &dir);
		proj_wall = (WALL_HIGHT / c->distances[i]) * proj_dist;
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
