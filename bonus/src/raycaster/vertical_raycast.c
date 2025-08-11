/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vertical_raycast.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbousset <mbousset@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 15:49:58 by mbousset          #+#    #+#             */
/*   Updated: 2025/08/11 17:44:08 by mbousset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "array.h"
#include "raycaster_bs.h"

void	process_ray(t_raycaster *c, t_frame_state *state, int ray_index)
{
	double	ray_ang;

	ray_ang = calculate_ray_angle(state, c, ray_index);
	if (can_reuse_ray(state, c, ray_index))
		reuse_ray_data(c, state, ray_index, ray_ang);
	else
		cast_new_ray(c, state, ray_index, ray_ang);
}

void	get_steps_v(t_pair *step, bool left, double ray_ang)
{
	step->x = WALL_WIDTH * (-left + !left);
	step->y = step->x * tan(ray_ang);
}

void	get_v_inter(t_point *next, bool left, double ray_ang)
{
	next->x = floor(get_game()->player.p.x / WALL_WIDTH) * WALL_WIDTH;
	if (!left)
		next->x += WALL_WIDTH;
	next->y = get_game()->player.p.y + (next->x - get_game()->player.p.x)
		* tan(ray_ang);
}

typedef struct s_doorhit
{
	double	dist;
	int		grid_x;
	int		grid_y;
	double	wall_x;
	int		dir;
}			t_doorhit;

double	check_door_vhit(t_rayinfo *ray, double *wall_x, int *dir, int *door_x,
		int *door_y)
{
	const t_game	*g = get_game();
	t_pair			p;
	int				player_tile_x;
	int				player_tile_y;

	player_tile_x = (int)(g->player.p.x / WALL_WIDTH);
	player_tile_y = (int)(g->player.p.y / WALL_WIDTH);
	p.x = (g->player.p.x / WALL_WIDTH);
	p.y = (g->player.p.y / WALL_WIDTH);
	if (g->data.map.arr[(int)p.y][(int)p.x] == 'D' && g->data.map.arr[(int)p.y
		+ 1][(int)p.x] == '1' && g->data.map.arr[(int)p.y - 1][(int)p.x] == '1')
	{
		if ((fmod(g->player.p.x, WALL_WIDTH) <= WALL_WIDTH / 2) ^ ray->left)
		{
			ray->next.y -= WALL_WIDTH / 2 * tan(ray->ray_ang * (-ray->left
						+ !ray->left));
			ray->next.x -= WALL_WIDTH / 2 * (-ray->left + !ray->left);
			if (((int)(ray->next.x / WALL_WIDTH) == player_tile_x
					&& (int)(ray->next.y / WALL_WIDTH) == player_tile_y))
			{
				ray->map_p.x = (int)(ray->next.x / WALL_WIDTH);
				ray->map_p.y = (int)(ray->next.y / WALL_WIDTH);
				*door_x = ray->map_p.x;
				*door_y = ray->map_p.y;
				*wall_x = ray->next.y;
				*dir = DOOR;
				return (get_dist(g->player.p, ray->next));
			}
			else
			{
				ray->next.y += WALL_WIDTH / 2 * tan(ray->ray_ang * (-ray->left
							+ !ray->left));
				ray->next.x += WALL_WIDTH / 2 * (-ray->left + !ray->left);
			}
		}
	}
	if (g->data.map.arr[(int)ray->map_p.y][(int)ray->map_p.x] == 'D')
	{
		ray->next.y += WALL_WIDTH / 2 * tan(ray->ray_ang * (-ray->left
					+ !ray->left));
		ray->next.x += WALL_WIDTH / 2 * (-ray->left + !ray->left);
		ray->map_p.x = (int)(ray->next.x / WALL_WIDTH);
		ray->map_p.y = (int)(ray->next.y / WALL_WIDTH);
		*door_x = ray->map_p.x;
		*door_y = ray->map_p.y;
		*wall_x = ray->next.y;
		*dir = DOOR;
		return (get_dist(g->player.p, ray->next));
	}
	return (-1);
}

double	verti_dist(double ray_ang, double *wall_x, int *dir, t_door *next_door)
{
	t_point			map_p;
	t_point			next;
	t_pair			step;
	bool			left;
	const t_game	*g = get_game();
	t_rayinfo		ray;
	double			door_hit;
	t_door			door;
	double			tex_x;
	int				door_x;
	int				door_y;

	left = cos(ray_ang) < 0;
	get_v_inter(&next, left, ray_ang);
	get_steps_v(&step, left, ray_ang);
	while (true)
	{
		map_p.x = ((next.x - 1) * left + next.x * !left) / WALL_WIDTH;
		map_p.y = next.y / WALL_WIDTH;
		if (outside_map(map_p.x, map_p.y))
			break ;
		ray = (t_rayinfo){next, map_p, ray_ang, left};
		door_hit = check_door_vhit(&ray, wall_x, dir, &door_x, &door_y);
		if (door_hit != -1)
		{
			door = get_door(door_x, door_y);
			tex_x = fmod(*wall_x, WALL_WIDTH) / WALL_WIDTH
				* (g->graphics[DOOR].w / 9) + ((g->graphics[DOOR].w / 9)
					* door.frame);
			if (!get_t(get_slice_color(tex_x, g->graphics[DOOR].h / 2, DOOR,
						2)))
				return (*next_door = door, door_hit);
		}
		if (g->data.map.arr[(int)map_p.y][(int)map_p.x] == '1')
		{
			*wall_x = next.y;
			*dir = W_WALL * left + E_WALL * !left;
			return (get_dist(g->player.p, next));
		}
		next.x += step.x;
		next.y += step.y;
	}
	return (INFINITY);
}
