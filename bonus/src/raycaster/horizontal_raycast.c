/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   horizontal_raycast.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbousset <mbousset@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 15:50:02 by mbousset          #+#    #+#             */
/*   Updated: 2025/09/10 16:03:42 by mbousset         ###   ########.fr       */
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

int	get_direction(int up)
{
	if (up)
		return (-1);
	return (1);
}

bool	is_valid_door_position(int px, int py, t_rayinfo *ray)
{
	t_game	*g;

	g = get_game();
	return (px > 0 && px < g->data.map.map_w - 1 && py >= 0
		&& py < g->data.map.map_h && ft_strchr("DX", g->data.map.arr[py][px])
		&& g->data.map.arr[py][px + 1] == '1' && g->data.map.arr[py][px
		- 1] == '1' && ((fmod(g->player.p.y, WALL_WIDTH) <= WALL_WIDTH
				/ 2) ^ ray->up));
}

double	check_door_hhit(t_rayinfo *ray, double *wall_x, int *dir, t_pair *door)
{
	t_game	*g;
	int		px;
	int		py;
	int		direction;

	g = get_game();
	px = (int)(g->player.p.x / WALL_WIDTH);
	py = (int)(g->player.p.y / WALL_WIDTH);
	direction = get_direction(ray->up);
	if (is_valid_door_position(px, py, ray))
	{
		ray->next.y -= (WALL_WIDTH / 2) * direction;
		ray->next.x -= (WALL_WIDTH / 2) / tan(ray->ray_ang * direction)
			* direction;
		if ((int)(ray->next.x / WALL_WIDTH) == px && (int)(ray->next.y
				/ WALL_WIDTH) == py)
		{
			*door = (t_pair){px, py};
			*wall_x = ray->next.x;
			*dir = DOOR;
			return (get_dist(g->player.p, ray->next));
		}
		else
		{
			ray->next.y += (WALL_WIDTH / 2) * direction;
			ray->next.x += (WALL_WIDTH / 2) / tan(ray->ray_ang * direction)
				* direction;
		}
	}
	if (ft_strchr("DX", g->data.map.arr[(int)ray->map_p.y][(int)ray->map_p.x]))
	{
		ray->next.y += (WALL_WIDTH / 2) * direction;
		ray->next.x += (WALL_WIDTH / 2) / tan(ray->ray_ang) * direction;
		*door = (t_pair){(int)(ray->next.x / WALL_WIDTH), (int)(ray->next.y
				/ WALL_WIDTH)};
		*wall_x = ray->next.x;
		*dir = DOOR;
		return (get_dist(g->player.p, ray->next));
	}
	return (-1);
}

static void	update_next_point(t_point *next, t_pair *step)
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
