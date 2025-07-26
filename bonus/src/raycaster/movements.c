/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbousset <mbousset@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 15:39:57 by mbousset          #+#    #+#             */
/*   Updated: 2025/07/26 15:18:28 by mbousset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

static void	move_along_axes(t_game *game, double *new_x, double *new_y)
{
	if (get_key(KEY_UP, game)->press || get_key(ARROW_UP, game)->press)
	{
		*new_x += cos(game->player.angle) * MOVE_SPEED;
		*new_y += sin(game->player.angle) * MOVE_SPEED;
	}
	if (get_key(KEY_DOWN, game)->press || get_key(ARROW_DOWN, game)->press)
	{
		*new_x -= cos(game->player.angle) * MOVE_SPEED;
		*new_y -= sin(game->player.angle) * MOVE_SPEED;
	}
	if (get_key(KEY_LEFT, game)->press)
	{
		*new_x += sin(game->player.angle) * MOVE_SPEED;
		*new_y -= cos(game->player.angle) * MOVE_SPEED;
	}
	if (get_key(KEY_RIGHT, game)->press)
	{
		*new_x -= sin(game->player.angle) * MOVE_SPEED;
		*new_y += cos(game->player.angle) * MOVE_SPEED;
	}
}

static void	rotate_player(t_game *game)
{
	if (get_key(ARROW_LEFT, game)->press || get_key(ARROW_RIGHT, game)->press)
		game->player.moving = true;
	else
		game->player.moving = false;
	if (get_key(ARROW_LEFT, game)->press)
		game->player.angle -= ROTATE_SPEED;
	if (get_key(ARROW_RIGHT, game)->press)
		game->player.angle += ROTATE_SPEED;
	game->player.angle = normalize_angle(game->player.angle);
}

static void	jump_player(t_game *game)
{
	static int	step;

	game->player.jumping = false;
	if (step == 0 && get_key(KEY_SPACE, game)->press)
		step = JUMP_SPEED;
	else if (game->player.p.z >= 200)
		step = -JUMP_SPEED;
	else if (game->player.p.z <= 0)
	{
		step = 0;
		game->player.p.z = 0;
	}
	if (step != 0)
	{
		game->player.moving = true;
		game->player.jumping = true;
	}
	game->player.p.z += step;
}

static void	apply_movement(t_game *game, double new_x, double new_y)
{
	if (game->data.map.arr[(int)(new_y / WALL_WIDTH)][(int)(new_x
			/ WALL_WIDTH)] != '1' && game->data.map.arr[(int)(new_y
			/ WALL_WIDTH)][(int)(new_x / WALL_WIDTH)] != ' ')
	{
		game->player.moving = (game->player.p.x != new_x
				|| game->player.p.y != new_y) || game->player.moving;
		game->player.p.x = new_x;
		game->player.p.y = new_y;
	}
}

void	update_player(t_game *game)
{
	double	new_x;
	double	new_y;

	new_x = game->player.p.x;
	new_y = game->player.p.y;
	move_along_axes(game, &new_x, &new_y);
	rotate_player(game);
	jump_player(game);
	apply_movement(game, new_x, new_y);
}
