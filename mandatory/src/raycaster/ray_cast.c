/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_cast.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbousset <mbousset@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 15:39:30 by mbousset          #+#    #+#             */
/*   Updated: 2025/06/25 17:21:49 by mbousset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

//? NOTES :
// the number of rays that we trace is the width of the window because ( win_width = the number of horizontal pixels on the window )
// FOV (fieled of view is a constent angel that the player see from) == 60
// the unit of angel between each ray is determened by the number of rays in this formule ( d(alpha) = FOV/ray_num )
// hieght of player is predefined as 32 units ,a units maybe a pixel or more depened on how is the hieght of wall,... read more

//! in game loop :
// cast_rays(game);
// draw_3d_view(game);

// cast rays will return the distance between the player position and the intersection with the wall
int	cast_rays(t_game *game)
{
	(void)game;
	// the raycasting is trowing a ray a stright line of light in a derection and checking if it hit a obstacle you know its position
}

void	draw_3d_view(game)
{
	(void)game;
	// here cast rays sholud be embedded in the while loop loping on rays
	return ;
}
