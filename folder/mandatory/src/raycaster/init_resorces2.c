/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_resorces2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbousset <mbousset@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 16:04:06 by mbousset          #+#    #+#             */
/*   Updated: 2025/07/12 16:06:45 by mbousset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

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
