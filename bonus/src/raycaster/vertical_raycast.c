/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vertical_raycast.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbousset <mbousset@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 15:49:58 by mbousset          #+#    #+#             */
/*   Updated: 2025/09/18 09:26:06 by mbousset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycaster_bs.h"

bool	is_valid_vdoor_position(int px, int py, t_rayinfo *ray)
{
	t_game	*g;

	g = get_game();
	return (px > 0 && px < g->data.map.map_w - 1 && py >= 0
		&& py < g->data.map.map_h && ft_strchr("DX", g->data.map.arr[py][px])
		&& g->data.map.arr[py + 1][px] == '1' && g->data.map.arr[py
		- 1][px] == '1' && ((fmod(g->player.p.x, WALL_WIDTH) <= WALL_WIDTH
				/ 2) ^ ray->up));
}

double	check_vertical_door_hit(t_door_inf *f, t_rayinfo *ray,
		t_door *next_door)
{
	t_pair	door;
	t_door	d;
	double	door_hit;
	double	tex_x;

	door_hit = check_door_vhit(ray, f->wall_x, f->dir, &door);
	if (door_hit == -1)
		return (-1);
	d = get_door(door.x, door.y);
	tex_x = (fmod(*f->wall_x, WALL_WIDTH) / WALL_WIDTH + d.frame)
		* (get_game()->graphics[DOOR].w / get_game()->graphics[DOOR].frames);
	if (get_game()->data.map.arr[(int)d.pos.y][(int)d.pos.x] == 'X')
	{
		if (get_game()->exit.frame == get_game()->graphics[DOOR].frames - 1)
			*f->dir = PORTAL;
		*next_door = d;
		return (door_hit);
	}
	if (!get_t(get_slice_color(tex_x, get_game()->graphics[DOOR].h / 2, DOOR,
				2)))
		return (*next_door = d, door_hit);
	return (-1);
}

static double	check_wall_vhit(t_door_inf *f, t_rayinfo *ray, t_point *next)
{
	t_game	*g;

	g = get_game();
	if (g->data.map.arr[(int)ray->map_p.y][(int)ray->map_p.x] == '1')
	{
		*f->wall_x = next->y;
		*f->dir = W_WALL * ray->left + E_WALL * !ray->left;
		return (get_dist(g->player.p, *next));
	}
	return (-1);
}

double	get_v_dist(t_door_inf f, t_point next, t_pair step, t_door *next_door)
{
	t_game		*g;
	t_rayinfo	ray;
	double		hit;

	while (true)
	{
		ray.map_p.x = ((next.x - 1) * f.left + next.x * !f.left) / WALL_WIDTH;
		ray.map_p.y = next.y / WALL_WIDTH;
		if (outside_map(ray.map_p.x, ray.map_p.y))
			break ;
		ray = (t_rayinfo){next, ray.map_p, f.ray_ang, .left = f.left};
		hit = check_vertical_door_hit(&f, &ray, next_door);
		if (hit != -1)
			return (hit);
		hit = check_wall_vhit(&f, &ray, &next);
		if (hit != -1)
			return (hit);
		update_next_point(&next, &step);
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
	f = (t_door_inf){wall_x, dir, ray_ang, .left = left};
	get_v_inter(&next, left, ray_ang);
	get_steps_v(&step, left, ray_ang);
	return (get_v_dist(f, next, step, next_door));
}
