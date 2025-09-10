/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vertical_raycast.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbousset <mbousset@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 15:49:58 by mbousset          #+#    #+#             */
/*   Updated: 2025/09/10 15:12:18 by mbousset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "array.h"
#include "raycaster_bs.h"

void	process_ray(t_raycaster *c, t_frame_state *state, int ray_index)
{
	double	ray_ang;

	ray_ang = calculate_ray_angle(state, c, ray_index);
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

// Check if the player's tile is a valid vertical door
bool	is_player_on_vertical_door(t_pair p, t_game *g)
{
	return (ft_strchr("DX", g->data.map.arr[(int)p.y][(int)p.x])
		&& g->data.map.arr[(int)p.y + 1][(int)p.x] == '1'
		&& g->data.map.arr[(int)p.y - 1][(int)p.x] == '1');
}

// Apply the door offset (temporary shift)
void	apply_door_offset(t_rayinfo *ray)
{
	ray->next.y -= WALL_WIDTH / 2 * tan(ray->ray_ang * (-ray->left
				+ !ray->left));
	ray->next.x -= WALL_WIDTH / 2 * (-ray->left + !ray->left);
}

// Restore the door offset (undo shift if no hit)
void	restore_door_offset(t_rayinfo *ray)
{
	ray->next.y += WALL_WIDTH / 2 * tan(ray->ray_ang * (-ray->left
				+ !ray->left));
	ray->next.x += WALL_WIDTH / 2 * (-ray->left + !ray->left);
}

// Main: check if ray hits player's vertical door
double	check_player_vertical_door(t_rayinfo *ray, t_door_inf f, int *door_x,
		int *door_y)
{
	t_game	*g;
	t_pair	p;
	int		p_tile_x;
	int		p_tile_y;

	g = get_game();
	p.x = g->player.p.x / WALL_WIDTH;
	p.y = g->player.p.y / WALL_WIDTH;
	p_tile_x = (int)p.x;
	p_tile_y = (int)p.y;
	if (!is_player_on_vertical_door(p, g))
		return (-1);
	if ((fmod(g->player.p.x, WALL_WIDTH) <= WALL_WIDTH / 2) ^ ray->left)
	{
		apply_door_offset(ray);
		if ((int)(ray->next.x / WALL_WIDTH) == p_tile_x && (int)(ray->next.y
				/ WALL_WIDTH) == p_tile_y)
			return (ray->map_p.x = p_tile_x, ray->map_p.y = p_tile_y,
				*door_x = ray->map_p.x, *door_y = ray->map_p.y,
				*(f.wall_x) = ray->next.y, *(f.dir) = DOOR,
				get_dist(g->player.p, ray->next));
		restore_door_offset(ray);
	}
	return (-1);
}

double	check_standard_vertical_door(t_rayinfo *ray, t_door_inf f, int *door_x,
		int *door_y)
{
	t_game	*g;

	g = get_game();
	if (!ft_strchr("DX", g->data.map.arr[(int)ray->map_p.y][(int)ray->map_p.x]))
		return (-1);
	ray->next.y += WALL_WIDTH / 2 * tan(ray->ray_ang * (-ray->left
				+ !ray->left));
	ray->next.x += WALL_WIDTH / 2 * (-ray->left + !ray->left);
	ray->map_p.x = (int)(ray->next.x / WALL_WIDTH);
	ray->map_p.y = (int)(ray->next.y / WALL_WIDTH);
	*door_x = ray->map_p.x;
	*door_y = ray->map_p.y;
	*(f.wall_x) = ray->next.y;
	*(f.dir) = DOOR;
	return (get_dist(g->player.p, ray->next));
}

double	check_door_vhit(t_rayinfo *ray, t_door_inf f, int *door_x, int *door_y)
{
	double	res;

	res = check_player_vertical_door(ray, f, door_x, door_y);
	if (res != -1)
		return (res);
	return (check_standard_vertical_door(ray, f, door_x, door_y));
}

// === VERTICAL HELPERS ===
t_rayinfo	init_vertical_ray(t_point next, t_point map_p, double ray_ang,
		bool left)
{
	return ((t_rayinfo){next, map_p, ray_ang, left});
}

bool	is_wall_hit(t_point map_p)
{
	t_game	*g;

	g = get_game();
	return (g->data.map.arr[(int)map_p.y][(int)map_p.x] == '1');
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
	int		door_x;
	int		door_y;
	double	door_hit;
	t_door	door;

	door_hit = check_door_vhit(&ray, f, &door_x, &door_y);
	if (door_hit == -1)
		return (-1);
	door = get_door(door_x, door_y);
	door_hit = handle_vertical_door_hit(door_hit, &door, f, next_door);
	return (door_hit);
}

// === RAY LOOP ===
double	get_v_dist(t_door_inf f, t_point next, t_pair step, t_door *next_door)
{
	t_point		map_p;
	t_rayinfo	ray;
	double		door_hit;

	while (true)
	{
		map_p.x = ((next.x - 1) * f.left + next.x * !f.left) / WALL_WIDTH;
		map_p.y = next.y / WALL_WIDTH;
		if (outside_map(map_p.x, map_p.y))
			break ;
		ray = init_vertical_ray(next, map_p, f.ray_ang, f.left);
		door_hit = check_vertical_door_hit(f, ray, next_door);
		if (door_hit != -1)
			return (door_hit);
		if (is_wall_hit(map_p))
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

// === MAIN FUNCTION ===
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
