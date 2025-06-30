/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbousset <mbousset@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 15:39:30 by mbousset          #+#    #+#             */
/*   Updated: 2025/06/30 19:10:39 by mbousset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

#define WALL_HIGHT 100

// TODO : do a header file for raycaster
typedef struct s_raycaster
{
	int			num_rays;
	double		angle_step;
	double		start_angle;
	double		*distances;
}				t_raycaster;

void	init_raycaster(t_raycaster *caster)
{
	t_game	*game;

	game = get_game();
	caster->num_rays = game->win_w;
	caster->angle_step = FOV_ANGLE / caster->num_rays;
	caster->distances = malloc(sizeof(double) * game->win_w);
}

double	get_ray_angle(int ray, t_raycaster caster)
{
	return (caster.start_angle + ray * caster.angle_step);
}
static double	verti_dist(double ray_ang, double *wall_x)
{
	t_game	*game;
	t_point	h_intersection;
	char	cell;
	int		facing_right;
	int		map_y;
	int		map_x;

	int x_step, y_step;
	facing_right = ray_ang > M_PI_2 && ray_ang < 3 * M_PI_2;
	game = get_game();
	h_intersection.x = floor(game->player.p.x / TILE_SIZE) * TILE_SIZE;
	h_intersection.x += facing_right ? -0.0001 : TILE_SIZE;
	h_intersection.y = game->player.p.y + ((h_intersection.y - game->player.p.y)
			/ tan(ray_ang));
	y_step = TILE_SIZE * (facing_right ? -1 : 1);
	x_step = y_step / tan(ray_ang);
	while (true)
	{
		map_y = (int)(h_intersection.y / TILE_SIZE);
		map_x = (int)(h_intersection.x / TILE_SIZE);
		// printf(" x = %d, y = %d\n", map_x, map_y);
		if (map_y < 0 || map_y >= game->win_h / TILE_SIZE || map_x < 0
			|| map_x >= game->win_w / TILE_SIZE)
			break ;
		cell = game->data.map.arr[map_y][map_x];
		if (cell == '1')
		{
			if (facing_right)
				*wall_x = h_intersection.y;
			else
				*wall_x = TILE_SIZE - h_intersection.y;
			return (get_distance(game->player.p, h_intersection));
		}
		h_intersection.y += y_step;
		h_intersection.x += x_step;
	}
	return (-1);
}

static double	horiz_dist(double ray_ang, double *wall_x)
{
	t_game	*game;
	t_point	v_intersection;
	char	cell;
	int		facing_up;
	int		map_y;
	int		map_x;

	int x_step, y_step;
	facing_up = ray_ang < M_PI;
	game = get_game();
	v_intersection.y = floor(game->player.p.y / TILE_SIZE) * TILE_SIZE;
	v_intersection.y += facing_up ? -0.0001 : TILE_SIZE;
	v_intersection.x = game->player.p.x + ((v_intersection.y - game->player.p.y)
			/ tan(ray_ang));
	y_step = TILE_SIZE * (facing_up ? -1 : 1);
	x_step = y_step / tan(ray_ang);
	while (true)
	{
		map_y = (int)(v_intersection.y / TILE_SIZE);
		map_x = (int)(v_intersection.x / TILE_SIZE);
		if (map_y < 0 || map_y >= game->win_h / TILE_SIZE || map_x < 0
			|| map_x >= game->win_w / TILE_SIZE)
			break ;
		cell = game->data.map.arr[map_y][map_x];
		if (cell == '1')
		{
			if (facing_up)
				*wall_x = v_intersection.x;
			else
				*wall_x = TILE_SIZE - v_intersection.x;
			return (get_distance(game->player.p, v_intersection));
		}
		v_intersection.y += y_step;
		v_intersection.x += x_step;
	}
	return (-1);
}

double	get_closest_hit_dist(double ray_angel, double *wall_x)
{
	double	h_distance;
	double	v_distance;
	t_game	*game;

	game = get_game();
	h_distance = horiz_dist(ray_angel, wall_x) * cos(ray_angel
			- game->player.angle);
	v_distance = verti_dist(ray_angel, wall_x) * cos(ray_angel
			- game->player.angle);
	if (h_distance < v_distance)
		return (h_distance);
	return (v_distance);
}

void	draw_wall_slice(i, proj_wall, wall_x)
{
	double	tex_x;
	int		distance_from_top;
	int		tex_y;
	double	tex_x;
	int		distance_from_top;
	int		tex_y;
	int wall_top;
	int wall_bottom;

	wall_top = (get_game()->win_h / 2) - (proj_wall / 2);
	wall_bottom = wall_top + proj_wall;
	if (wall_top < 0)
		wall_top = 0;
	if (wall_bottom > WIN_HEIGHT)
		wall_bottom = WIN_HEIGHT;
	if (!hit_vertical)
	{
		tex_x = fmod(hor_x, TILE_SIZE) / TILE_SIZE * game->hor_wal_img.w;
		for (int y = 0; y < wall_top; y++)
			my_mlx_pixel_put(game->player_view_buf, i, y, 0xaed6f1
				* (y < wall_top - WALL_EDGE / 2));
		for (int y = wall_top; y < wall_bottom; y++)
		{
			distance_from_top = y - wall_top;
			tex_y = (int)((double)distance_from_top / proj_wall
					* game->hor_wal_img.h);
			pixel_color = get_color(&game->hor_wal_img, (int)tex_x, tex_y);
			my_mlx_pixel_put(game->player_view_buf, i, y, pixel_color);
		}
		for (int y = wall_bottom; y < WIN_HEIGHT; y++)
			my_mlx_pixel_put(game->player_view_buf, i, y, 0xfdfefe
				* (y > wall_bottom + WALL_EDGE));
	}
	else
	{
		tex_x = fmod(vert_y, TILE_SIZE) / TILE_SIZE * get_game()->hor_wal_img.w;
		
		for (int y = 0; y < wall_top; y++)
			my_mlx_pixel_put(game->player_view_buf, i, y, 0xaed6f1
				* (y < wall_top - WALL_EDGE / 2));
		for (int y = wall_top; y < wall_bottom; y++)
		{
			distance_from_top = y - wall_top;
			tex_y = (int)((double)distance_from_top / wall_height
					* game->hor_wal_img.h);
			pixel_color = get_color(&game->hor_wal_img, (int)tex_x, tex_y);
			my_mlx_pixel_put(game->player_view_buf, i, y, pixel_color);
		}
		for (int y = wall_bottom; y < WIN_HEIGHT; y++)
			my_mlx_pixel_put(game->player_view_buf, i, y, 0xfdfefe
				* (y > wall_bottom + WALL_EDGE));
	}
	return ;
}

void	draw_3d_view(t_game *game, t_raycaster *caster)
{
	double	ray_angel;
	double	distance;
	double	distance_proj_plane;
	double	proj_wall;
	double	wall_x;
	int		i;

	caster->start_angle = game->player.angle - FOV_ANGLE / 2;
	i = 0;
	while (i < caster->num_rays)
	{
		ray_angel = get_ray_angle(i, *caster);
		caster->distances[i] = get_closest_hit_dist(ray_angel, &wall_x);
		distance_proj_plane = (game->win_w / 2) / tan(FOV_ANGLE / 2);
		proj_wall = WALL_HIGHT / caster->distances[i] * distance_proj_plane;
		draw_wall_slice(i, proj_wall, wall_x);
		i++;
	}
	return ;
}

void	cast_rays(t_game *game)
{
	t_raycaster	caster;

	init_raycaster(&caster);
	draw_3d_view(game, &caster);
}



//TODO : refacture this code based on the down code , tomorow


// #include "raycaster.h"

// #define WALL_HIGHT 100

// static int	is_oob(t_point tile)
// {
// 	t_game	*g;

// 	g = get_game();
// 	if (tile.x < 0 || tile.y < 0)
// 		return (1);
// 	if (tile.x >= g->win_w / TILE_SIZE)
// 		return (1);
// 	if (tile.y >= g->win_h / TILE_SIZE)
// 		return (1);
// 	return (0);
// }

// static double	horiz_dist(double ang, double *wall_x, int *dir)
// {
// 	t_point	p;
// 	t_point	step;
// 	t_point	tile;
// 	int		up;

// 	up = (ang < M_PI);
// 	p.y = floor(get_game()->player.p.y / TILE_SIZE) * TILE_SIZE;
// 	if (up)
// 		p.y -= 0.0001;
// 	else
// 		p.y += TILE_SIZE;
// 	p.x = get_game()->player.p.x + (p.y - get_game()->player.p.y) / tan(ang);
// 	step.y = TILE_SIZE;
// 	if (up)
// 		step.y *= -1;
// 	step.x = step.y / tan(ang);
// 	while (1)
// 	{
// 		tile.x = (int)(p.x / TILE_SIZE);
// 		tile.y = (int)(p.y / TILE_SIZE);
// 		if (is_oob(tile)
// 			|| get_game()->data.map.arr[(int)tile.y][(int)tile.x] == '1')
// 			break ;
// 		p.x += step.x;
// 		p.y += step.y;
// 	}
// 	if (!is_oob(tile)
// 		&& get_game()->data.map.arr[(int)tile.y][(int)tile.x] == '1')
// 		*wall_x = p.x / TILE_SIZE;
// 	*dir = S_WALL;
// 	if (up)
// 		*dir = N_WALL;
// 	return (get_distance(get_game()->player.p, p));
// }

// static double	verti_dist(double ang, double *wall_x, int *dir)
// {
// 	t_point	p;
// 	t_point	step;
// 	t_point	tile;
// 	int		left;

// 	left = (ang > M_PI_2 && ang < 3 * M_PI_2);
// 	p.x = floor(get_game()->player.p.x / TILE_SIZE) * TILE_SIZE;
// 	if (left)
// 		p.x -= 0.0001;
// 	else
// 		p.x += TILE_SIZE;
// 	p.y = get_game()->player.p.y + (p.x - get_game()->player.p.x) * tan(ang);
// 	step.x = TILE_SIZE;
// 	if (left)
// 		step.x *= -1;
// 	step.y = step.x * tan(ang);
// 	while (1)
// 	{
// 		tile.x = (int)(p.x / TILE_SIZE);
// 		tile.y = (int)(p.y / TILE_SIZE);
// 		if (is_oob(tile)
// 			|| get_game()->data.map.arr[(int)tile.y][(int)tile.x] == '1')
// 			break ;
// 		p.x += step.x;
// 		p.y += step.y;
// 	}
// 	if (!is_oob(tile)
// 		&& get_game()->data.map.arr[(int)tile.y][(int)tile.x] == '1')
// 		*wall_x = p.x / TILE_SIZE;
// 	*dir = W_WALL;
// 	if (left)
// 		*dir = E_WALL;
// 	return (get_distance(get_game()->player.p, p));
// }

// static double	closest_hit(double ang, double *wall_x, int *dir)
// {
// 	double	h;
// 	double	v;
// 	double	h_x;
// 	double	v_x;
// 	t_game	*g;

// 	g = get_game();
// 	h = horiz_dist(ang, &h_x, dir);
// 	v = verti_dist(ang, &v_x, dir);
// 	h *= cos(ang - g->player.angle);
// 	v *= cos(ang - g->player.angle);
// 	if (h < v)
// 	{
// 		*wall_x = h_x;
// 		return (h);
// 	}
// 	*wall_x = v_x;
// 	return (v);
// }

// void	init_raycaster(t_raycaster *c)
// {
// 	t_game	*g;

// 	g = get_game();
// 	c->num_rays = g->win_w;
// 	c->angle_step = FOV_ANGLE / c->num_rays;
// 	c->distances = malloc(sizeof(double) * c->num_rays);
// }

// unsigned int	get_slice_color(int x, int y, int dir, int section)
// {
// 	if (section == 1)
// 		return (get_game()->data.ceiling_clr);
// 	else if (section == 2)
// 		return (get_color(get_game()->graphics[dir], x, y));
// 	return (get_game()->data.ceiling_clr);
// }

// typedef struct s_section
// {
// 	int number;
// 	int start;
// 	int			end;
// 	int			win_x;
// 	int			wall_x;
// 	int			wall_h;
// 	t_graphic	wall;

// }				t_section;

// void	draw_section(t_section section)
// {
// 	int	i;
// 	int	tex_x;

// 	int tex_y;
// 	int d_from_top, color;
// 	i = section.start;
// 	while (i < section.end)
// 	{
// 		if (section.number == 2)
// 		{
// 			d_from_top = i - section.start;
// 			tex_y = (int)((double)d_from_top / section.wall_h
// 					* get_game()->graphics[section.wall].h);
// 			tex_x = fmod(section.wall_x, TILE_SIZE) / TILE_SIZE
// 				* get_game()->graphics[section.wall].w;
// 		}
// 		color = get_color(get_game()->graphics[section.wall], (int)tex_x,
// 				tex_y);
// 		my_mlx_pixel_put(get_game()->display, section.win_x, i, color);
// 		i++;
// 	}
// }

// void	draw_wall_slice(int w_x, double wall_h, int x, int dir)
// {
// 	int			i;
// 	int			color;
// 	double		tex_x;
// 	const int	wall_top = get_game()->win_h - wall_h;
// 	const int	wall_bottom = wall_top + wall_h;
// 	int			distance_from_top;
// 	int			tex_y;

	
// 	draw_section(0, wall_top, 1);
// 	draw_section(wall_top, wall_bottom, 2);
// 	draw_section(wall_bottom, get_game()->win_h, 3);

// }

// static void	draw_3d_view(t_game *g, t_raycaster *c)
// {
// 	int		i;
// 	double	ray_ang;
// 	double	proj_dist;
// 	double	proj_wall;
// 	double	wall_x;
// 	int		dir;

// 	c->start_angle = g->player.angle - FOV_ANGLE / 2;
// 	proj_dist = (g->win_w / 2) / tan(FOV_ANGLE / 2);
// 	i = -1;
// 	while (++i < c->num_rays)
// 	{
// 		ray_ang = c->start_angle + i * c->angle_step;
// 		c->distances[i] = closest_hit(ray_ang, &wall_x, &dir);
// 		proj_wall = WALL_HIGHT / c->distances[i] * proj_dist;
// 		draw_wall_slice(i, proj_wall, wall_x, dir);
// 		// draw wall slice needs the num of ray the x in the wall and ,
// 		// the wall direction, and the projected wall_hight
// 	}
// }

// void	cast_rays(t_game *game)
// {
// 	t_raycaster	caster;

// 	init_raycaster(&caster);
// 	draw_3d_view(game, &caster);
// 	free(caster.distances);
// }
