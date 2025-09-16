/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   horizontal_raycast.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbousset <mbousset@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 15:50:02 by mbousset          #+#    #+#             */
/*   Updated: 2025/09/16 09:32:28 by mbousset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycaster_bs.h"

void	update_next_point(t_point *next, t_pair *step)
{
	next->x += step->x;
	next->y += step->y;
}

static double	check_wall_hit(t_door_inf *f, t_rayinfo *ray, t_point *next)
{
	t_game	*g;

	g = get_game();
	if (g->data.map.arr[(int)ray->map_p.y][(int)ray->map_p.x] == '1')
	{
		*f->wall_x = next->x;
		*f->dir = N_WALL * f->up + S_WALL * !f->up;
		return (get_dist(g->player.p, *next));
	}
	return (-1);
}

double	do_door_hit(t_door_inf *f, t_rayinfo *ray, t_door *next_door)
{
	t_pair	door;
	t_door	d;
	double	door_hit;
	double	tex_x;

	door_hit = check_door_hhit(ray, f->wall_x, f->dir, &door);
	if (door_hit == -1)
		return (-1);
	d = get_door(door.x, door.y);
	tex_x = fmod(*f->wall_x, WALL_WIDTH) / WALL_WIDTH
		* (get_game()->graphics[DOOR].w / get_game()->graphics[DOOR].frames)
		+ ((get_game()->graphics[DOOR].w / get_game()->graphics[DOOR].frames)
			* d.frame);
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

double	get_h_dist(t_door_inf f, t_point next, t_pair step, t_door *next_door)
{
	t_game		*g;
	t_rayinfo	ray;
	double		hit;

	g = get_game();
	while (1)
	{
		ray.map_p.x = next.x / WALL_WIDTH;
		ray.map_p.y = ((next.y - 1) * f.up + next.y * !f.up) / WALL_WIDTH;
		if (outside_map(ray.map_p.x, ray.map_p.y))
			break ;
		ray = (t_rayinfo){next, ray.map_p, f.ray_ang, .up = f.up};
		hit = do_door_hit(&f, &ray, next_door);
		if (hit != -1)
			return (hit);
		hit = check_wall_hit(&f, &ray, &next);
		if (hit != -1)
			return (hit);
		update_next_point(&next, &step);
	}
	return (INFINITY);
}

double	horiz_dist(double ray_ang, double *wall_x, int *dir, t_door *next_door)
{
	t_point		next;
	t_pair		step;
	bool		up;
	t_door_inf	f;

	up = sin(ray_ang) < 0;
	f = (t_door_inf){wall_x, dir, ray_ang, .up = up};
	get_h_inter(&next, up, ray_ang);
	get_steps_h(&step, up, ray_ang);
	return (get_h_dist(f, next, step, next_door));
}
