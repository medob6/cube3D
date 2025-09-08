/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   horizontal_raycast.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbousset <mbousset@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 15:50:02 by mbousset          #+#    #+#             */
/*   Updated: 2025/09/08 18:03:20 by mbousset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

// // === BASIC RAY STEPS ===
// void	get_steps_h(t_pair *step, bool up, double ray_ang)
// {
// 	step->y = WALL_WIDTH * (-up + !up);
// 	step->x = step->y / tan(ray_ang);
// }

// void	get_h_inter(t_point *next, bool up, double ray_ang)
// {
// 	next->y = floor(get_game()->player.p.y / WALL_WIDTH) * WALL_WIDTH;
// 	if (!up)
// 		next->y += WALL_WIDTH;
// 	next->x = get_game()->player.p.x + (next->y - get_game()->player.p.y)
// 		/ tan(ray_ang);
// }

// // === DOOR HIT CHECK ===

// // ---------------- PLAYER DOOR HELPERS ----------------
// static bool	player_on_door_tile(t_rayinfo *ray)
// {
// 	const t_game	*g = get_game();
// 	int				tile_x;
// 	int				tile_y;

// 	tile_x = (int)(g->player.p.x / WALL_WIDTH);
// 	tile_y = (int)(g->player.p.y / WALL_WIDTH);
// 	return (ft_strchr("DX", g->data.map.arr[tile_y][tile_x])
// 		&& g->data.map.arr[tile_y][tile_x + 1] == '1'
// 		&& g->data.map.arr[tile_y][tile_x - 1] == '1');
// }

// static void	adjust_ray_for_player_door(t_rayinfo *ray, bool up)
// {
// 	ray->next.y -= WALL_WIDTH / 2 * (-up + !up);
// 	ray->next.x -= (WALL_WIDTH / 2) / tan(ray->ray_ang) * (-up + !up);
// }

// static void	restore_ray_for_player_door(t_rayinfo *ray, bool up)
// {
// 	ray->next.y += WALL_WIDTH / 2 * (-up + !up);
// 	ray->next.x += (WALL_WIDTH / 2) / tan(ray->ray_ang) * (-up + !up);
// }

// static double	handle_player_hdoor(t_rayinfo *ray, t_doorhit h)
// {
// 	const t_game	*g = get_game();
// 	bool			up;
// 	int				tile_x;
// 	int				tile_y;

// 	up = h.left;
// 	tile_x = (int)(g->player.p.x / WALL_WIDTH);
// 	tile_y = (int)(g->player.p.y / WALL_WIDTH);
// 	if (!player_on_door_tile(ray))
// 		return (-1);
// 	if ((fmod(g->player.p.y, WALL_WIDTH) <= WALL_WIDTH / 2) ^ up)
// 	{
// 		adjust_ray_for_player_door(ray, up);
// 		if ((int)(ray->next.x / WALL_WIDTH) == tile_x && (int)(ray->next.y
// 				/ WALL_WIDTH) == tile_y)
// 		{
// 			ray->map_p.x = tile_x;
// 			ray->map_p.y = tile_y;
// 			return (*h.door_x = ray->map_p.x, *h.door_y = ray->map_p.y,
// 				*h.wall_x = ray->next.x, *h.dir = DOOR, get_dist(g->player.p,
// 					ray->next));
// 		}
// 		restore_ray_for_player_door(ray, up);
// 	}
// 	return (-1);
// }

// // ---------------- STANDARD DOOR ----------------
// static void	adjust_ray_for_standard_door(t_rayinfo *ray, bool up)
// {
// 	ray->next.y += WALL_WIDTH / 2 * (-up + !up);
// 	ray->next.x += (WALL_WIDTH / 2) / tan(ray->ray_ang) * (-up + !up);
// 	ray->map_p.x = (int)(ray->next.x / WALL_WIDTH);
// 	ray->map_p.y = (int)(ray->next.y / WALL_WIDTH);
// }

// static double	handle_standard_hdoor(t_rayinfo *ray, t_doorhit h)
// {
// 	const t_game	*g = get_game();

// 	if (!ft_strchr("DX", g->data.map.arr[(int)ray->map_p.y][(int)ray->map_p.x]))
// 		return (-1);
// 	adjust_ray_for_standard_door(ray, h.left);
// 	*h.door_x = ray->map_p.x;
// 	*h.door_y = ray->map_p.y;
// 	*h.wall_x = ray->next.x;
// 	*h.dir = DOOR;
// 	return (get_dist(get_game()->player.p, ray->next));
// }

// // ---------------- MAIN HORIZONTAL DOOR CHECK ----------------
// double	check_door_hhit(t_rayinfo *ray, t_doorhit h)
// {
// 	double	res;

// 	res = handle_player_hdoor(ray, h);
// 	if (res != -1)
// 		return (res);
// 	return (handle_standard_hdoor(ray, h));
// }

// // === HIT DISPATCH ===
// static bool	update_map_pos_h(t_point *map_p, t_point next, bool up)
// {
// 	map_p->x = next.x / WALL_WIDTH;
// 	map_p->y = ((next.y - 1) * up + next.y * (!up)) / WALL_WIDTH;
// 	return (!outside_map(map_p->x, map_p->y));
// }

// double	process_door_hit(double door_hit, double wall_x, t_doorhit h,
// 		t_door *next_door)
// {
// 	const t_game	*g = get_game();
// 	t_door			door;
// 	double			tex_x;

// 	if (door_hit == -1)
// 		return (-1);
// 	door = get_door(*h.door_x, *h.door_y);
// 	tex_x = fmod(wall_x, WALL_WIDTH) / WALL_WIDTH * (g->graphics[DOOR].w
// 			/ g->graphics[DOOR].frames) + ((g->graphics[DOOR].w
// 				/ g->graphics[DOOR].frames) * door.frame);
// 	if (g->data.map.arr[(int)door.pos.y][(int)door.pos.x] == 'X')
// 	{
// 		if (g->exit.frame == g->graphics[DOOR].frames - 1)
// 			*h.dir = PORTAL;
// 		return (*next_door = door, door_hit);
// 	}
// 	if (!get_t(get_slice_color(tex_x, g->graphics[DOOR].h / 2, DOOR, 2)))
// 		return (*next_door = door, door_hit);
// 	return (-1);
// }


// static double	check_hits_h(t_rayinfo ray, t_doorhit h, t_door *next_door)
// {
// 	double			door_hit;
// 	double			res;
// 	const t_game	*g = get_game();

// 	door_hit = check_door_hhit(&ray, h);
// 	res = process_door_hit(door_hit, *h.wall_x, h, next_door);
// 	if (res != -1)
// 		return (res);
// 	if (g->data.map.arr[(int)ray.map_p.y][(int)ray.map_p.x] == '1')
// 	{
// 		*h.wall_x = ray.next.x;
// 		*h.dir = N_WALL * ray.left + S_WALL * !ray.left;
// 		return (get_dist(g->player.p, ray.next));
// 	}
// 	return (-1);
// }

// double	horiz_dist(double ray_ang, double *wall_x, int *dir, t_door *next_door)
// {
// 	t_hray	h;

// 	h.h = (t_doorhit){wall_x, dir, &h.door_x, &h.door_y, sin(ray_ang) < 0};
// 	get_h_inter(&h.next, h.h.left, ray_ang);
// 	get_steps_h(&h.step, h.h.left, ray_ang);
// 	while (update_map_pos_h(&h.map_p, h.next, h.h.left))
// 	{
// 		h.ray = (t_rayinfo){h.next, h.map_p, ray_ang, h.h.left};
// 		h.ray.result = check_hits_h(h.ray, h.h, next_door);
// 		if (h.ray.result != -1)
// 			return (h.ray.result);
// 		h.next.x += h.step.x;
// 		h.next.y += h.step.y;
// 	}
// 	return (INFINITY);
// }


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
	t_game	*g = get_game();
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
