/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omben-ch <omben-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 16:14:23 by omben-ch          #+#    #+#             */
/*   Updated: 2025/09/16 16:14:26 by omben-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_bs.h"

void	parse_input(t_game *game, int ac, char **av)
{
	t_fcub	fcub;

	parse_and_get_data(&fcub, ac, av);
	game->toeg = fcub.steps_to_exit * 10 / 60;
	if (game->toeg > 15)
		game->toeg = 15;
	if (game->toeg <= 0)
		game->toeg = 1;
	game->toeg--;
	game->data.paths[N_WALL] = fcub.n_path;
	game->data.paths[W_WALL] = fcub.w_path;
	game->data.paths[E_WALL] = fcub.e_path;
	game->data.paths[S_WALL] = fcub.s_path;
	game->data.ceiling_clr = get_rgb(&fcub, fcub.c_color);
	game->data.floor_clr = get_rgb(&fcub, fcub.f_color);
	game->data.map.arr = fcub.map;
	game->data.map.map_h = count_list(fcub.map);
	game->data.map.map_w = get_size_of_long_line(&fcub);
	game->doors = fcub.door;
	game->nb_of_doors = fcub.nb_door;
	game->exit = *fcub.exit;
	free(fcub.exit);
	game->passed = false;
	game->tmp_time = 0;
}

long long	get_current_time_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (((long long)(tv.tv_sec) *1000) + (tv.tv_usec / 1000));
}

void	print_err(char *msg)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(msg, 2);
	cleanup(EXIT_FAILURE);
}

bool	door_is_closed(t_door door)
{
	int	last_fram;

	last_fram = get_game()->graphics[DOOR].frames - 1;
	if (door.frame == last_fram)
		return (true);
	return (false);
}

void	start_closing_door(t_door *door)
{
	door->closing = true;
	door->last_update = get_current_time_ms();
}
