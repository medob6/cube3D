/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   v_raycaster_rayhelper.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbousset <mbousset@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 09:41:08 by mbousset          #+#    #+#             */
/*   Updated: 2025/09/16 09:41:20 by mbousset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycaster_bs.h"

void	restore_door_offset(t_rayinfo *ray)
{
	ray->next.y += WALL_WIDTH / 2 * tan(ray->ray_ang * (-ray->left
				+ !ray->left));
	ray->next.x += WALL_WIDTH / 2 * (-ray->left + !ray->left);
}

double	ver_door_res(t_rayinfo *ray, int *door_x, int *door_y)
{
	t_game	*g;

	g = get_game();
	if (get_door(*door_x, *door_y).frame == g->graphics[DOOR].frames - 1)
		return (restore_door_offset(ray), -1);
	else
		return (get_dist(g->player.p, ray->next));
}

double	check_player_vertical_door(t_rayinfo *ray, t_door_inf f, int *door_x,
		int *door_y)
{
	t_game	*g;
	t_pair	p;
	int		p_tile_x;
	int		p_tile_y;
	double	result;

	g = get_game();
	p.x = g->player.p.x / WALL_WIDTH;
	p.y = g->player.p.y / WALL_WIDTH;
	p_tile_x = (int)p.x;
	p_tile_y = (int)p.y;
	if (!is_player_on_vertical_door(p, g))
		return (-1);
	if ((fmod(g->player.p.x, WALL_WIDTH) < WALL_WIDTH / 2) ^ ray->left)
	{
		apply_door_offset(ray);
		if ((int)(ray->next.x / WALL_WIDTH) == p_tile_x && (int)(ray->next.y
				/ WALL_WIDTH) == p_tile_y)
			return (ray->map_p.x = p_tile_x, ray->map_p.y = p_tile_y,
				*door_x = ray->map_p.x, *door_y = ray->map_p.y,
				*(f.wall_x) = ray->next.y, *(f.dir) = DOOR, ver_door_res(ray,
					door_x, door_y));
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
