/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   horizontal_raycast.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbousset <mbousset@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 15:50:02 by mbousset          #+#    #+#             */
/*   Updated: 2025/08/09 17:13:52 by mbousset         ###   ########.fr       */
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

	up = ray->left;
	if (g->data.map.arr[(int)(g->player.p.y / WALL_WIDTH)][(int)(g->player.p.x
			/ WALL_WIDTH)] == 'D' && g->data.map.arr[(int)(g->player.p.y
			/ WALL_WIDTH)][(int)(g->player.p.x / WALL_WIDTH) + 1] == '1'
		&& g->data.map.arr[(int)(g->player.p.y
			/ WALL_WIDTH)][(int)(g->player.p.x / WALL_WIDTH) - 1] == '1')
	{
		if ((fmod(g->player.p.y, WALL_WIDTH) <= WALL_WIDTH / 2) ^ up)
		{
			ray->next.y -= WALL_WIDTH / 2 * (-up + !up);
			ray->next.x -= (WALL_WIDTH / 2) / tan(ray->ray_ang) * (-up + !up);
			ray->map_p.x = (int)(ray->next.x / WALL_WIDTH);
			ray->map_p.y = (int)(ray->next.y / WALL_WIDTH);
			*door_x = ray->map_p.x;
			*door_y = ray->map_p.y;
			*wall_x = ray->next.x;
			*dir = DOOR;
			return (get_dist(g->player.p, ray->next));
		}
	}
	if (g->data.map.arr[(int)ray->map_p.y][(int)ray->map_p.x] == 'D')
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
				* (g->graphics[DOOR].w / 9) + ((g->graphics[DOOR].w / 9)
					* door.frame);
			
			if (!get_t(get_slice_color(tex_x, g->graphics[DOOR].h / 2, DOOR,
						2)))
				return (*next_door = door,door_hit);
		}
		if (g->data.map.arr[(int)map_p.y][(int)map_p.x] == '1')
			return (*wall_x = next.x, *dir = N_WALL * up + S_WALL * !up,
				get_dist(g->player.p, next));
		next.x += step.x;
		next.y += step.y;
	}
	return (INFINITY);
}
