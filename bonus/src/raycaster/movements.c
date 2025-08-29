/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbousset <mbousset@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 15:39:57 by mbousset          #+#    #+#             */
/*   Updated: 2025/08/27 15:38:03 by mbousset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_bs.h"

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

t_door		get_door(int x, int y);

bool	valid_door_pos(double new_x, double new_y)
{
	char	cell;
	char	u_cell;
	char	d_cell;
	char	l_cell;
	char	r_cell;
	char	**map;

	map = get_game()->data.map.arr;
	cell = map[(int)(new_y / WALL_WIDTH)][(int)(new_x / WALL_WIDTH)];
	// static int n;
	// here if the door is in last frame we can move through it
	if (get_door((int)(new_x / WALL_WIDTH), (int)(new_y
				/ WALL_WIDTH)).frame == 8)
	{
		if (cell == 'D')
			return (true);
	}
	u_cell = map[(int)(new_y / WALL_WIDTH) + 1][(int)(new_x / WALL_WIDTH)];
	d_cell = map[(int)(new_y / WALL_WIDTH) - 1][(int)(new_x / WALL_WIDTH)];
	l_cell = map[(int)(new_y / WALL_WIDTH)][(int)(new_x / WALL_WIDTH) + 1];
	r_cell = map[(int)(new_y / WALL_WIDTH)][(int)(new_x / WALL_WIDTH) - 1];
	if (ft_strchr("DX", cell))
	{
		if (u_cell == '1' && d_cell == '1')
		{
			if (((fmod(new_x, WALL_WIDTH) < ((WALL_WIDTH / 2.0) - WALL_WIDTH
							* 0.1)) || fmod(new_x, WALL_WIDTH) > ((WALL_WIDTH
							/ 2.0) + WALL_WIDTH * 0.1)))
				return (true);
		}
		else if (r_cell == '1' && l_cell == '1')
		{
			if (((fmod(new_y, WALL_WIDTH) < ((WALL_WIDTH / 2.0) - WALL_WIDTH
							* 0.1)) || fmod(new_y, WALL_WIDTH) > ((WALL_WIDTH
							/ 2.0) + WALL_WIDTH * 0.1)))
				return (true);
		}
	}
	if (cell == 'X' && get_door((int)(new_x / WALL_WIDTH), (int)(new_y
				/ WALL_WIDTH)).frame == 8)
		get_game()->passed = true;
	// printf("n %d\n",n++);
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
		{
			return (get_game()->doors[i]);
		}
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
	jump_player(game);
	apply_movement(game, new_x, new_y);
}

// i should do this

// lunch ray folow it until you found a wall save all door intersections in one array

// in drawing calculate slice hight for each door door per door and map the pixel from fram sprite for the specific door if the x pixel is transparent go to next
//  until you find a hit that is not transparnet then draw it
// do it for each piwel in the hight ,
// if the last door pix is transparent just draw wall

// so we should have an array of distences ro door from the ray casting ,
// loop over it

// task after it refactor all the code clean it merge and do next tasks
