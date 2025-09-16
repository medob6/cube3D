/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vertical_raycast.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbousset <mbousset@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 15:49:58 by mbousset          #+#    #+#             */
/*   Updated: 2025/09/16 09:44:50 by mbousset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycaster_bs.h"

// === VERTICAL HELPERS ===
t_rayinfo	init_vertical_ray(t_point next, t_point map_p, double ray_ang,
		bool left)
{
	return ((t_rayinfo){next, map_p, ray_ang, left});
}

// === DOOR HANDLING ===
double	handle_vertical_door_hit(double door_hit, t_door *door, t_door_inf f,
		t_door *next_door)
{
	t_game	*g;
	double	tex_x;

	g = get_game();
	tex_x = fmod(*f.wall_x, WALL_WIDTH) / WALL_WIDTH * (g->graphics[DOOR].w
			/ g->graphics[DOOR].frames) + ((g->graphics[DOOR].w
				/ (g->graphics[DOOR].frames)) * door->frame);
	if ((int)door->pos.y < 0 || (int)door->pos.y >= g->data.map.map_h
		|| (int)door->pos.x < 0 || (int)door->pos.x >= g->data.map.map_w)
		return (-1);
	if (g->data.map.arr[(int)door->pos.y][(int)door->pos.x] == 'X')
	{
		if (g->exit.frame == g->graphics[DOOR].frames - 1)
			*f.dir = PORTAL;
		return (*next_door = *door, door_hit);
	}
	if (!get_t(get_slice_color(tex_x, g->graphics[DOOR].h / 2, DOOR, 2)))
		return (*next_door = *door, door_hit);
	return (-1);
}

// === HANDLE DOOR HIT ===
double	check_vertical_door_hit(t_door_inf f, t_rayinfo ray, t_door *next_door)
{
	int			door_x;
	int			door_y;
	double		door_hit;
	t_door		door;
	static int	c = 0;

	door_hit = check_door_vhit(&ray, f, &door_x, &door_y);
	if (door_hit == -1)
		return (-1);
	door = get_door(door_x, door_y);
	door_hit = handle_vertical_door_hit(door_hit, &door, f, next_door);
	return (door_hit);
}

double	get_v_dist(t_door_inf f, t_point next, t_pair step, t_door *next_door)
{
	t_point		map_p;
	t_rayinfo	ray;
	double		dist_door_hit;

	while (true)
	{
		map_p.x = ((next.x - 1) * f.left + next.x * !f.left) / WALL_WIDTH;
		map_p.y = next.y / WALL_WIDTH;
		if (outside_map(map_p.x, map_p.y))
			break ;
		ray = init_vertical_ray(next, map_p, f.ray_ang, f.left);
		dist_door_hit = check_vertical_door_hit(f, ray, next_door);
		if (dist_door_hit != -1)
			return (dist_door_hit);
		if (get_game()->data.map.arr[(int)map_p.y][(int)map_p.x] == '1')
		{
			*(f.wall_x) = next.y;
			*(f.dir) = W_WALL * f.left + E_WALL * !f.left;
			return (get_dist(get_game()->player.p, next));
		}
		next.x += step.x;
		next.y += step.y;
	}
	return (INFINITY);
}

double	verti_dist(double ray_ang, double *wall_x, int *dir, t_door *next_door)
{
	t_point		next;
	t_pair		step;
	bool		left;
	t_door_inf	f;

	left = cos(ray_ang) < 0;
	f = (t_door_inf){wall_x, dir, ray_ang, left};
	get_v_inter(&next, left, ray_ang);
	get_steps_v(&step, left, ray_ang);
	return (get_v_dist(f, next, step, next_door));
}
