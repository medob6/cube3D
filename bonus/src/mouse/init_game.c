/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_resources_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omben-ch <omben-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 13:34:28 by omben-ch          #+#    #+#             */
/*   Updated: 2025/09/11 10:14:54 by omben-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_bs.h"

void init_doors_exit(t_game *game)
{
    int i;

    i = 0;
    while (i < game->nb_of_doors)
	{
        game->doors[i].in_range = false;
        game->doors[i].frame = 0;
        game->doors[i].closing = false;
        game->doors[i].opening = false;
        game->doors[i].animating = false;
	    i++;
	}
    game->exit.in_range = false;
    game->exit.frame = 0;
    game->exit.closing = false;
    game->exit.opening = false;
    game->exit.animating = false;
}

void init_resources_game(t_game *game)
{
    init_doors_exit(game);
    game->player = game->player_info;
}
