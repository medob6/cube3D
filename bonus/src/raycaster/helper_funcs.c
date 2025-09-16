/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_funcs.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbousset <mbousset@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 16:04:06 by mbousset          #+#    #+#             */
/*   Updated: 2025/09/16 09:19:20 by mbousset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_bs.h"

t_game	*get_game(void)
{
	static t_game	game;

	return (&game);
}

bool	is_valid_dir(char dir)
{
	if (dir == 'N' || dir == 'S' || dir == 'E' || dir == 'W')
		return (true);
	return (false);
}

double	deg_to_rad(double a)
{
	return (a * M_PI / 180.0);
}

double	get_view_angel(char dir)
{
	if (dir == 'E')
		return (deg_to_rad(0));
	else if (dir == 'S')
		return (deg_to_rad(90));
	else if (dir == 'W')
		return (deg_to_rad(180));
	else if (dir == 'N')
		return (deg_to_rad(270));
	return (1);
}

double	correct_dist(double raw_d, double ang)
{
	return (raw_d * cos(normalize_angle(ang - get_game()->player.angle)));
}
