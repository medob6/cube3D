/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster_process.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbousset <mbousset@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 09:36:25 by mbousset          #+#    #+#             */
/*   Updated: 2025/09/16 09:43:35 by mbousset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

bool	is_player_on_vertical_door(t_pair p, t_game *g)
{
	return (ft_strchr("DX", g->data.map.arr[(int)p.y][(int)p.x])
		&& g->data.map.arr[(int)p.y + 1][(int)p.x] == '1'
		&& g->data.map.arr[(int)p.y - 1][(int)p.x] == '1');
}

void	apply_door_offset(t_rayinfo *ray)
{
	ray->next.y -= WALL_WIDTH / 2 * tan(ray->ray_ang * (-ray->left
				+ !ray->left));
	ray->next.x -= WALL_WIDTH / 2 * (-ray->left + !ray->left);
}
