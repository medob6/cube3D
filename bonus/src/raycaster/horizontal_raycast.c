/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   horizontal_raycast.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbousset <mbousset@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 15:50:02 by mbousset          #+#    #+#             */
/*   Updated: 2025/09/07 19:17:10 by mbousset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycaster_bs.h"

void	init_raycaster(t_raycaster *c)
{
	t_game	*g;

	g = get_game();
	c->num_rays = g->win_w;
	c->angle_step = FOV_ANGLE / c->num_rays;
	c->lines = ft_calloc(c->num_rays, sizeof(t_sec));
	c->prev_lines = ft_calloc(c->num_rays, sizeof(t_sec));
}

void	get_h_inter(t_point *next, bool facing_up, double ray_ang)
{
	next->y = floor(get_game()->player.p.y / WALL_WIDTH) * WALL_WIDTH;
	if (!facing_up)
		next->y += WALL_WIDTH;
	next->x = get_game()->player.p.x + (next->y - get_game()->player.p.y)
		/ tan(ray_ang);
}

void	get_steps_h(t_pair *step, bool up, double ray_ang)
{
	step->y = WALL_WIDTH * (-up + !up);
	step->x = step->y / tan(ray_ang);
}

double	check_door_hhit(t_rayinfo *ray, double *wall_x, int *dir, int *door_x,
		int *door_y)
{
	const t_game	*g = get_game();
	bool			up;
	int				player_tile_x;
	int				player_tile_y;
	static int		j;

	player_tile_x = (int)(g->player.p.x / WALL_WIDTH);
	player_tile_y = (int)(g->player.p.y / WALL_WIDTH);
	up = ray->left;
	if (ft_strchr("DX", g->data.map.arr[player_tile_y][player_tile_x])
		&& g->data.map.arr[player_tile_y][player_tile_x + 1] == '1'
		&& g->data.map.arr[player_tile_y][player_tile_x - 1] == '1')
	{
		if ((fmod(g->player.p.y, WALL_WIDTH) <= WALL_WIDTH / 2) ^ up)
		{
			ray->next.y -= WALL_WIDTH / 2 * (-up + !up);
			ray->next.x -= (WALL_WIDTH / 2) / tan(ray->ray_ang) * (-up + !up);
			if (((int)(ray->next.x / WALL_WIDTH) == player_tile_x
					&& (int)(ray->next.y / WALL_WIDTH) == player_tile_y))
			{
				ray->map_p.x = (int)(ray->next.x / WALL_WIDTH);
				ray->map_p.y = (int)(ray->next.y / WALL_WIDTH);
				*door_x = ray->map_p.x;
				*door_y = ray->map_p.y;
				*wall_x = ray->next.x;
				*dir = DOOR;
				return (get_dist(g->player.p, ray->next));
			}
			else
			{
				ray->next.y += WALL_WIDTH / 2 * (-up + !up);
				ray->next.x += (WALL_WIDTH / 2) / tan(ray->ray_ang) * (-up
						+ !up);
			}
		}
	}
	if (ft_strchr("DX", g->data.map.arr[(int)ray->map_p.y][(int)ray->map_p.x]))
	{
		ray->next.y += WALL_WIDTH / 2 * (-up + !up);
		ray->next.x += (WALL_WIDTH / 2) / tan(ray->ray_ang) * (-up + !up);
		ray->map_p.x = (int)(ray->next.x / WALL_WIDTH);
		ray->map_p.y = (int)(ray->next.y / WALL_WIDTH);
		*door_x = ray->map_p.x;
		*door_y = ray->map_p.y;
		*wall_x = ray->next.x;
		*dir = DOOR;
		return (get_dist(g->player.p, ray->next));
	}
	return (-1);
}
double	horiz_dist(double ray_ang, double *wall_x, int *dir, t_door *next_door)
{
	t_point			map_p;
	t_point			next;
	t_pair			step;
	bool			up;
	const t_game	*g = get_game();
	t_rayinfo		ray;
	double			door_hit;
	t_door			door;
	double			tex_x;
	int				door_x;
	int				door_y;

	up = sin(ray_ang) < 0;
	get_h_inter(&next, up, ray_ang);
	get_steps_h(&step, up, ray_ang);
	while (true)
	{
		map_p.x = next.x / WALL_WIDTH;
		map_p.y = ((next.y - 1) * (up) + next.y * (!up)) / WALL_WIDTH;
		if (outside_map(map_p.x, map_p.y))
			break ;
		ray = (t_rayinfo){next, map_p, ray_ang, up};
		door_hit = check_door_hhit(&ray, wall_x, dir, &door_x, &door_y);
		if (door_hit != -1)
		{
			door = get_door(door_x, door_y);
			tex_x = fmod(*wall_x, WALL_WIDTH) / WALL_WIDTH
				* (g->graphics[DOOR].w / 10) + ((g->graphics[DOOR].w / 10)
					* door.frame);
			if (g->data.map.arr[(int)door.pos.y][(int)door.pos.x] == 'X')
			{
				if (g->exit.frame == g->graphics[DOOR].frames - 1)
					*dir = PORTAL;
				return (*next_door = door, door_hit);
			}
			if (!get_t(get_slice_color(tex_x, g->graphics[DOOR].h / 2, DOOR,
						2)))
				return (*next_door = door, door_hit);
		}
		if (g->data.map.arr[(int)map_p.y][(int)map_p.x] == '1')
			return (*wall_x = next.x, *dir = N_WALL * up + S_WALL * !up,
				get_dist(g->player.p, next));
		next.x += step.x;
		next.y += step.y;
	}
	return (INFINITY);
}

// #include "raycaster_bs.h"

// void	init_raycaster(t_raycaster *c)
// {
// 	t_game	*g;

// 	g = get_game();
// 	c->num_rays = g->win_w;
// 	c->angle_step = FOV_ANGLE / c->num_rays;
// 	c->lines = ft_calloc(c->num_rays, sizeof(t_sec));
// 	c->prev_lines = ft_calloc(c->num_rays, sizeof(t_sec));
// }

// void	get_h_inter(t_point *next, bool facing_up, double ray_ang)
// {
// 	next->y = floor(get_game()->player.p.y / WALL_WIDTH) * WALL_WIDTH;
// 	if (!facing_up)
// 		next->y += WALL_WIDTH;
// 	next->x = get_game()->player.p.x + (next->y - get_game()->player.p.y)
// 		/ tan(ray_ang);
// }

// void	get_steps_h(t_pair *step, bool up, double ray_ang)
// {
// 	step->y = WALL_WIDTH * (-up + !up);
// 	step->x = step->y / tan(ray_ang);
// }

// typedef struct s_door_hit
// {
// 	double	*wall_x;
// 	int		*dir;
// 	int		*door_x;
// 	int		*door_y;
// }			t_door_hit;

// static bool	player_in_hdoor_tile(const t_game *g, int x, int y)
// {
// 	if (!ft_strchr("DX", g->data.map.arr[y][x]))
// 		return (false);
// 	if (g->data.map.arr[y][x + 1] != '1')
// 		return (false);
// 	if (g->data.map.arr[y][x - 1] != '1')
// 		return (false);
// 	return (true);
// }

// static void	adjust_ray(t_rayinfo *ray, bool up, int sign)
// {
// 	ray->next.y += sign * WALL_WIDTH / 2 * (-up + !up);
// 	ray->next.x += sign * (WALL_WIDTH / 2) / tan(ray->ray_ang) * (-up + !up);
// }

// static bool	ray_hits_door_tile(t_rayinfo *ray, t_door_hit *hit)
// {
// 	ray->map_p.x = (int)(ray->next.x / WALL_WIDTH);
// 	ray->map_p.y = (int)(ray->next.y / WALL_WIDTH);
// 	*hit->door_x = ray->map_p.x;
// 	*hit->door_y = ray->map_p.y;
// 	*hit->wall_x = ray->next.x;
// 	*hit->dir = DOOR;
// 	return (true);
// }

// double	check_door_hhit(t_rayinfo *ray, t_door_hit *hit)
// {
// 	const t_game	*g = get_game();
// 	int				x;
// 	int				y;
// 	bool			up;

// 	x = (int)(g->player.p.x / WALL_WIDTH);
// 	y = (int)(g->player.p.y / WALL_WIDTH);
// 	up = ray->left;
// 	if (player_in_hdoor_tile(g, x, y) && ((fmod(g->player.p.y,
// 					WALL_WIDTH) <= WALL_WIDTH / 2) ^ up))
// 	{
// 		adjust_ray(ray, up, -1);
// 		if ((int)(ray->next.x / WALL_WIDTH) == x && (int)(ray->next.y
// 				/ WALL_WIDTH) == y)
// 			return (get_dist(g->player.p, ray->next) * ray_hits_door_tile(ray,
// 					hit));
// 		adjust_ray(ray, up, 1);
// 	}
// 	if (ft_strchr("DX", g->data.map.arr[(int)ray->map_p.y][(int)ray->map_p.x]))
// 	{
// 		adjust_ray(ray, up, 1);
// 		return (get_dist(g->player.p, ray->next) * ray_hits_door_tile(ray,
// 				hit));
// 	}
// 	return (-1);
// }

// static bool	handle_door_hit(t_rayinfo *ray, t_door_hit *hit,
//		t_door *next_door,
// 		double *wall_x)
// {
// 	const t_game	*g = get_game();
// 	t_door			door;
// 	double			tex_x;

// 	door = get_door(*hit->door_x, *hit->door_y);
// 	tex_x = fmod(*wall_x, WALL_WIDTH) / WALL_WIDTH * (g->graphics[DOOR].w / 10)
// 		+ ((g->graphics[DOOR].w / 10) * door.frame);
// 	if (g->data.map.arr[(int)door.pos.y][(int)door.pos.x] == 'X')
// 	{
// 		if (g->exit.frame == g->graphics[DOOR].frames - 1)
// 			*hit->dir = PORTAL;
// 		*next_door = door;
// 		return (true);
// 	}
// 	if (!get_t(get_slice_color(tex_x, g->graphics[DOOR].h / 2, DOOR, 2)))
// 	{
// 		*next_door = door;
// 		return (true);
// 	}
// 	return (false);
// }

// static bool	handle_wall_hit(t_point map_p, t_point next, double *wall_x,
// 		int *dir, bool up)
// {
// 	const t_game	*g = get_game();

// 	if (g->data.map.arr[(int)map_p.y][(int)map_p.x] != '1')
// 		return (false);
// 	*wall_x = next.x;
// 	*dir = N_WALL * up + S_WALL * !up;
// 	return (true);
// }

// double	horiz_dist(double ray_ang, double *wall_x, int *dir,
		//t_door *next_door)
// {
// 	t_point		map_p;
// 	t_point		next;
// 	t_pair		step;
// 	bool		up;
// 	t_rayinfo	ray;
// 	double		door_hit;
// 	t_door_hit	hit;
// 	int			door_x;
// 	int			door_y;

// 	up = sin(ray_ang) < 0;
// 	get_h_inter(&next, up, ray_ang);
// 	get_steps_h(&step, up, ray_ang);
// 	hit.wall_x = wall_x;
// 	hit.dir = dir;
// 	hit.door_x = &door_x;
// 	hit.door_y = &door_y;
// 	while (true)
// 	{
// 		map_p.x = next.x / WALL_WIDTH;
// 		map_p.y = ((next.y - 1) * up + next.y * (!up)) / WALL_WIDTH;
// 		if (outside_map(map_p.x, map_p.y))
// 			break ;
// 		ray = (t_rayinfo){next, map_p, ray_ang, up};
// 		door_hit = check_door_hhit(&ray, &hit);
// 		if (door_hit != -1 && handle_door_hit(&ray, &hit, next_door, wall_x))
// 			return (door_hit);
// 		if (handle_wall_hit(map_p, next, wall_x, dir, up))
// 			return (get_dist(get_game()->player.p, next));
// 		next.x += step.x;
// 		next.y += step.y;
// 	}
// 	return (INFINITY);
// }
