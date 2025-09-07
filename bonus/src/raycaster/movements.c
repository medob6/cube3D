/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbousset <mbousset@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 15:39:57 by mbousset          #+#    #+#             */
/*   Updated: 2025/09/07 17:58:46 by mbousset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_bs.h"

static void	move_along_axes(t_game *game, double *new_x, double *new_y)
{
	if (get_key(KEY_UP, game)->press)
	{
		*new_x += cos(game->player.angle) * MOVE_SPEED;
		*new_y += sin(game->player.angle) * MOVE_SPEED;
	}
	if (get_key(KEY_DOWN, game)->press)
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
	if (get_key(ARROW_LEFT, game)->press || get_key(ARROW_RIGHT, game)->press
		|| get_key(ARROW_UP, game)->press || get_key(ARROW_DOWN, game)->press)
		game->player.moving = true;
	else
		game->player.moving = false;
	if (get_key(ARROW_LEFT, game)->press)
		game->player.angle -= ROTATE_SPEED;
	if (get_key(ARROW_RIGHT, game)->press)
		game->player.angle += ROTATE_SPEED;
	if (get_key(ARROW_UP, game)->press)
	{
		if (game->player.p.z < game->win_h)
			game->player.p.z += 20;
	}
	if (get_key(ARROW_DOWN, game)->press)
	{
		if (game->player.p.z > -game->win_h)
			game->player.p.z -= 20;
	}
	game->player.angle = normalize_angle(game->player.angle);
}

static bool	is_door_fully_open(double new_x, double new_y, char cell)
{
	if (get_door((int)(new_x / WALL_WIDTH), (int)(new_y
				/ WALL_WIDTH)).frame == get_game()->graphics[DOOR].frames - 1)
		return (cell == 'D');
	return (false);
}

static bool	is_vertical_door_aligned(double new_x)
{
	double	offset;

	offset = fmod(new_x, WALL_WIDTH);
	return (offset < (WALL_WIDTH / 2.0 - WALL_WIDTH * 0.1)
		|| offset > (WALL_WIDTH / 2.0 + WALL_WIDTH * 0.1));
}

static bool	is_horizontal_door_aligned(double new_y)
{
	double	offset;

	offset = fmod(new_y, WALL_WIDTH);
	return (offset < (WALL_WIDTH / 2.0 - WALL_WIDTH * 0.1)
		|| offset > (WALL_WIDTH / 2.0 + WALL_WIDTH * 0.1));
}

static bool	is_door_passable(double new_x, double new_y, char **map, char cell)
{
	char	u_cell;
	char	d_cell;
	char	l_cell;
	char	r_cell;
	int		x;
	int		y;

	x = (int)(new_x / WALL_WIDTH);
	y = (int)(new_y / WALL_WIDTH);
	u_cell = map[y + 1][x];
	d_cell = map[y - 1][x];
	l_cell = map[y][x + 1];
	r_cell = map[y][x - 1];
	if (ft_strchr("DX", cell))
	{
		if (u_cell == '1' && d_cell == '1')
			return (is_vertical_door_aligned(new_x));
		else if (r_cell == '1' && l_cell == '1')
			return (is_horizontal_door_aligned(new_y));
	}
	return (false);
}

bool	valid_door_pos(double new_x, double new_y)
{
	char	**map;
	char	cell;
	int		x;
	int		y;

	map = get_game()->data.map.arr;
	x = (int)(new_x / WALL_WIDTH);
	y = (int)(new_y / WALL_WIDTH);
	cell = map[y][x];
	if (is_door_fully_open(new_x, new_y, cell))
		return (true);
	if (is_door_passable(new_x, new_y, map, cell))
		return (true);
	if (cell == 'X' && get_door(x, y).frame == get_game()->graphics[DOOR].frames - 1)
		get_game()->passed = true;
	return (false);
}

t_door	get_door(int x, int y)
{
	int	i;

	i = 0;
	if (get_game()->exit.pos.x == x && get_game()->exit.pos.y == y)
		return (get_game()->exit);
	while (i < get_game()->nb_of_doors)
	{
		if (get_game()->doors[i].pos.x == x && get_game()->doors[i].pos.y == y)
			return (get_game()->doors[i]);
		i++;
	}
}

static void	apply_movement(t_game *game, double new_x, double new_y)
{
	char	cell;

	if (fmod(new_y, WALL_WIDTH) == 0)
		new_y -= 0.001;
	if (fmod(new_x, WALL_WIDTH) == 0)
		new_x -= 0.001;
	cell = game->data.map.arr[(int)(new_y / WALL_WIDTH)][(int)(new_x
			/ WALL_WIDTH)];
	if (cell == '0' || (ft_strchr("DX", cell) && valid_door_pos(new_x, new_y)))
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
	apply_movement(game, new_x, new_y);
}
