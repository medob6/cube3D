/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbousset <mbousset@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 15:39:30 by mbousset          #+#    #+#             */
/*   Updated: 2025/07/02 21:26:46 by mbousset         ###   ########.fr       */
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
		return (get_game()->data.ceiling_clr);
	else if (section == 2)
	{
		if ((x >= 0 && x < get_game()->graphics[dir].w) && (y >= 0
				&& y < get_game()->graphics[dir].h))
			return (get_color(get_game()->graphics[dir], x, y));
	}
	else if (section == 3)
		return (get_game()->data.floor_clr);
	return (0);
}

void	draw_section(int start, int end, int num, t_sec_inf *section)
{
	int		i;
	t_image	tex;
	double	d_from_top;
	int		color;

	int tex_x, tex_y;
	i = start;
	tex = get_game()->graphics[section->wall];
	while (i <= end)
	{
		if (num == 2)
		{
			d_from_top = i - start + section->tex_offset;
			tex_y = (d_from_top / section->wall_h) * tex.h;
			tex_x = fmod(section->wall_x, TILE_SIZE) / TILE_SIZE * tex.w;
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
	section->tex_offset = 0;
	return (section);
}

void	draw_wall_slice(int w_x, double wall_h, int x, int dir)
{
	int			wall_top;
	t_sec_inf	*section;
	int			wall_bottom;
	
	section = init_section(w_x, wall_h, x, dir);
	wall_top = get_game()->win_h / 2 - wall_h / 2;
	wall_bottom = wall_top + wall_h;
	if (wall_top < 0)
	{
		section->tex_offset = -wall_top;
		wall_top = 0;
	}
	if (wall_bottom > get_game()->win_h)
		wall_bottom = get_game()->win_h;

	draw_section(0, wall_top, 1, section);
	draw_section(wall_top, wall_bottom, 2, section);
	draw_section(wall_bottom, get_game()->win_h, 3, section);
	free(section);
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

// #include "raycaster.h"
// #define WALL_HIGHT 64

// // Structure to cache ray hit data
// typedef struct s_ray_cache
// {
// 	double			distance;
// 	double			wall_x;
// 	int				direction;
// 	double			angle;
// 	bool			valid;
// }					t_ray_cache;

// // Global cache variables
// static t_ray_cache	*g_ray_cache = NULL;
// static int			g_cache_size = 0;
// static double		g_cached_player_x = -1;
// static double		g_cached_player_y = -1;
// static bool			g_cache_initialized = false;

// double	get_ray_angle(int ray, t_raycaster caster)
// {
// 	return (caster.start_angle + ray * caster.angle_step);
// }

// // Initialize or resize the ray cache
// void	init_ray_cache(int num_rays)
// {
// 	if (g_ray_cache && g_cache_size != num_rays)
// 	{
// 		free(g_ray_cache);
// 		g_ray_cache = NULL;
// 	}
// 	if (!g_ray_cache)
// 	{
// 		g_ray_cache = malloc(sizeof(t_ray_cache) * num_rays);
// 		g_cache_size = num_rays;
// 	}
// 	// Mark all cache entries as invalid
// 	for (int i = 0; i < num_rays; i++)
// 	{
// 		g_ray_cache[i].valid = false;
// 	}
// 	g_cache_initialized = true;
// }

// // Check if player position has changed
// bool	player_position_changed(t_game *game)
// {
// 	return (g_cached_player_x != game->player.p.x
// 		|| g_cached_player_y != game->player.p.y);
// }

// // Update cached player position
// void	update_cached_position(t_game *game)
// {
// 	g_cached_player_x = game->player.p.x;
// 	g_cached_player_y = game->player.p.y;
// }

// // Find cached ray data for a specific angle
// t_ray_cache	*find_cached_ray(double angle, int num_rays)
// {
// 	if (!g_cache_initialized)
// 		return (NULL);
// 	for (int i = 0; i < num_rays; i++)
// 	{
// 		if (g_ray_cache[i].valid && fabs(normalize_angle(g_ray_cache[i].angle)
// 				- normalize_angle(angle)) < 0.0001)
// 		{
// 			return (&g_ray_cache[i]);
// 		}
// 	}
// 	return (NULL);
// }

// // Store ray data in cache
// void	cache_ray_data(int ray_index, double angle, double distance,
// 		double wall_x, int direction)
// {
// 	if (g_cache_initialized && ray_index >= 0 && ray_index < g_cache_size)
// 	{
// 		g_ray_cache[ray_index].angle = angle;
// 		g_ray_cache[ray_index].distance = distance;
// 		g_ray_cache[ray_index].wall_x = wall_x;
// 		g_ray_cache[ray_index].direction = direction;
// 		g_ray_cache[ray_index].valid = true;
// 	}
// }

// static double	verti_dist(double ray_ang, double *wall_x, int *dir)
// {
// 	t_game	*game;
// 	t_point	v_intersection;
// 	bool	facing_left;
// 	double	x_step;
// 	double	y_step;

// 	game = get_game();
// 	facing_left = cos(ray_ang) < 0;
// 	double next_x, next_y;
// 	int map_x, map_y;
// 	x_step = TILE_SIZE * (facing_left ? -1 : 1);
// 	y_step = x_step * tan(ray_ang);
// 	v_intersection.x = floor(game->player.p.x / TILE_SIZE) * TILE_SIZE;
// 	if (!facing_left)
// 		v_intersection.x += TILE_SIZE;
// 	v_intersection.y = game->player.p.y + (v_intersection.x - game->player.p.x)
// 		* tan(ray_ang);
// 	next_x = v_intersection.x;
// 	next_y = v_intersection.y;
// 	while (true)
// 	{
// 		map_x = (int)((facing_left ? next_x - 1 : next_x) / TILE_SIZE);
// 		map_y = (int)(next_y / TILE_SIZE);
// 		if (map_x < 0 || map_x >= game->data.map.map_w || map_y < 0
// 			|| map_y >= game->data.map.map_h)
// 			break ;
// 		if (game->data.map.arr[map_y][map_x] == '1')
// 		{
// 			*wall_x = next_y;
// 			*dir = facing_left ? W_WALL : E_WALL;
// 			return (hypot(next_x - game->player.p.x, next_y
// 					- game->player.p.y));
// 		}
// 		next_x += x_step;
// 		next_y += y_step;
// 	}
// 	return (INFINITY);
// }

// static double	horiz_dist(double ray_ang, double *wall_x, int *dir)
// {
// 	t_game	*game;
// 	t_point	h_intersection;
// 	bool	facing_up;

// 	game = get_game();
// 	facing_up = sin(ray_ang) < 0;
// 	double next_x, next_y;
// 	double x_step, y_step;
// 	int map_x, map_y;
// 	y_step = TILE_SIZE * (facing_up ? -1 : 1);
// 	x_step = y_step / tan(ray_ang);
// 	h_intersection.y = floor(game->player.p.y / TILE_SIZE) * TILE_SIZE;
// 	if (!facing_up)
// 		h_intersection.y += TILE_SIZE;
// 	h_intersection.x = game->player.p.x + (h_intersection.y - game->player.p.y)
// 		/ tan(ray_ang);
// 	next_x = h_intersection.x;
// 	next_y = h_intersection.y;
// 	while (true)
// 	{
// 		map_x = (int)(next_x / TILE_SIZE);
// 		map_y = (int)((facing_up ? next_y - 1 : next_y) / TILE_SIZE);
// 		if (map_x < 0 || map_x >= game->data.map.map_w || map_y < 0
// 			|| map_y >= game->data.map.map_h)
// 			break ;
// 		if (game->data.map.arr[map_y][map_x] == '1')
// 		{
// 			*wall_x = next_x;
// 			*dir = facing_up ? N_WALL : S_WALL;
// 			return (hypot(next_x - game->player.p.x, next_y
// 					- game->player.p.y));
// 		}
// 		next_x += x_step;
// 		next_y += y_step;
// 	}
// 	return (INFINITY);
// }

// double	closest_hit(double ang, double *wall_x, int *dir)
// {
// 	t_game	*g;

// 	double h, v;
// 	double h_x, v_x;
// 	int h_dir, v_dir;
// 	g = get_game();
// 	h = horiz_dist(ang, &h_x, &h_dir);
// 	v = verti_dist(ang, &v_x, &v_dir);
// 	if (h < v)
// 	{
// 		*dir = h_dir;
// 		*wall_x = h_x;
// 		return (h * cos(normalize_angle(ang - g->player.angle)));
// 	}
// 	else
// 	{
// 		*dir = v_dir;
// 		*wall_x = v_x;
// 		return (v * cos(normalize_angle(ang - g->player.angle)));
// 	}
// }

// void	init_raycaster(t_raycaster *c)
// {
// 	t_game	*g;

// 	g = get_game();
// 	c->num_rays = g->win_w;
// 	c->angle_step = FOV_ANGLE / c->num_rays;
// 	c->distances = malloc(sizeof(double) * c->num_rays);
// 	// Initialize ray cache
// 	init_ray_cache(c->num_rays);
// }

// unsigned int	get_slice_color(int x, int y, int dir, int section)
// {
// 	if (section == 1)
// 		return (get_game()->data.ceiling_clr);
// 	else if (section == 2)
// 	{
// 		if ((x >= 0 && x < get_game()->graphics[dir].w) && (y >= 0
// 				&& y < get_game()->graphics[dir].h))
// 			return (get_color(get_game()->graphics[dir], x, y));
// 	}
// 	else if (section == 3)
// 		return (get_game()->data.floor_clr);
// 	return (0);
// }

// void	draw_section(int start, int end, int num, t_sec_inf *section)
// {
// 	int		i;
// 	t_image	tex;

// 	int tex_x, tex_y;
// 	i = start;
// 	int d_from_top, color;
// 	tex = get_game()->graphics[section->wall];
// 	while (i <= end)
// 	{
// 		if (num == 2)
// 		{
// 			d_from_top = i - start + section->texture_offset;
// 				// Add texture offset
// 			tex_y = ((double)d_from_top / section->wall_h) * tex.h;
// 			tex_x = fmod(section->wall_x, TILE_SIZE) / TILE_SIZE * tex.w;
// 			tex_x = fmax(0, fmin(tex_x, tex.w - 1));
// 			tex_y = fmax(0, fmin(tex_y, tex.h - 1));
// 		}
// 		color = get_slice_color(tex_x, tex_y, section->wall, num);
// 		my_mlx_pixel_put(get_game()->display, section->win_x, i, color);
// 		i++;
// 	}
// }

// t_sec_inf	*init_section(int w_x, double wall_h, int x, t_graphic dir)
// {
// 	t_sec_inf	*section;

// 	section = malloc(sizeof(t_sec_inf));
// 	section->wall_h = wall_h;
// 	section->wall = dir;
// 	section->wall_x = x;
// 	section->win_x = w_x;
// 	section->texture_offset = 0;
// 	return (section);
// }

// void	draw_wall_slice(int w_x, double wall_h, int x, int dir)
// {
// 	int			wall_top;
// 	t_sec_inf	*section;
// 	int			wall_bottom;
// 	int			texture_start_offset;

// 	texture_start_offset = 0;
// 	wall_top = get_game()->win_h / 2 - wall_h / 2;
// 	wall_bottom = wall_top + wall_h;
// 	// Calculate texture offset when wall is taller than screen
// 	if (wall_top < 0)
// 	{
// 		texture_start_offset = -wall_top;
// 			// How many pixels we skip from top of texture
// 		wall_top = 0;
// 	}
// 	if (wall_bottom > get_game()->win_h)
// 		wall_bottom = get_game()->win_h;
// 	section = init_section(w_x, wall_h, x, dir);
// 	section->texture_offset = texture_start_offset; // Store offset in section
// 	draw_section(0, wall_top, 1, section);
// 	draw_section(wall_top, wall_bottom, 2, section);
// 	draw_section(wall_bottom, get_game()->win_h, 3, section);
// 	free(section);
// }

// void	draw_3d_view(t_game *g, t_raycaster *c)
// {
// 	int			i;
// 	double		ray_ang;
// 	double		proj_dist;
// 	double		proj_wall;
// 	double		wall_x;
// 	int			dir;
// 	bool		position_changed;
// 	t_ray_cache	*cached_ray;

// 	c->start_angle = g->player.angle - FOV_ANGLE / 2;
// 	proj_dist = (g->win_w / 2) / tan(FOV_ANGLE / 2);
// 	// Check if player position changed
// 	position_changed = player_position_changed(g);
// 	i = -1;
// 	while (++i < c->num_rays)
// 	{
// 		ray_ang = normalize_angle(c->start_angle + i * c->angle_step);
// 		// Try to use cached data if position hasn't changed
// 		cached_ray = NULL;
// 		if (!position_changed)
// 		{
// 			cached_ray = find_cached_ray(ray_ang, c->num_rays);
// 		}
// 		if (cached_ray && cached_ray->valid)
// 		{
// 			// Use cached data
// 			c->distances[i] = cached_ray->distance;
// 			wall_x = cached_ray->wall_x;
// 			dir = cached_ray->direction;
// 		}
// 		else
// 		{
// 			// Calculate new ray data
// 			c->distances[i] = closest_hit(ray_ang, &wall_x, &dir);
// 			// Cache the result
// 			cache_ray_data(i, ray_ang, c->distances[i], wall_x, dir);
// 		}
// 		proj_wall = (WALL_HIGHT / c->distances[i]) * proj_dist;
// 		draw_wall_slice(i, proj_wall, wall_x, dir);
// 	}
// 	// Update cached position if it changed
// 	if (position_changed)
// 	{
// 		update_cached_position(g);
// 	}
// }

// void	cast_rays(t_game *game)
// {
// 	t_raycaster	caster;

// 	init_raycaster(&caster);
// 	draw_3d_view(game, &caster);
// 	free(caster.distances);
// }

// // Call this when cleaning up or when the game ends
// void	cleanup_ray_cache(void)
// {
// 	if (g_ray_cache)
// 	{
// 		free(g_ray_cache);
// 		g_ray_cache = NULL;
// 		g_cache_size = 0;
// 		g_cache_initialized = false;
// 	}
// }
