/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omben-ch <omben-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 09:35:56 by omben-ch          #+#    #+#             */
/*   Updated: 2025/09/13 18:42:55 by omben-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_bs.h"

void	freeing_list(char **list)
{
	int	i;

	i = 0;
	while (list && list[i])
	{
		free(list[i]);
		i++;
	}
	if (list)
		free(list[i]);
	free(list);
}

int	count_list(char **list)
{
	int	i;

	i = 0;
	while (list && list[i])
		i++;
	return (i);
}

int	count_line(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (i > 2147483647)
			return (-1);
		i++;
	}
	return ((int)i);
}

void	freeing_data(t_fcub *fcub)
{
	int	i;

	i = 0;
	free(fcub->n_path);
	free(fcub->w_path);
	free(fcub->e_path);
	free(fcub->s_path);
	free(fcub->f_color);
	free(fcub->c_color);
	while (fcub->map && fcub->map[i])
	{
		free(fcub->map[i]);
		i++;
	}
	if (fcub->map)
		free(fcub->map[i]);
	free(fcub->map);
}

void	next(t_fcub *fcub, int x, int y, int *door)
{
	if (fcub->map[y][x] == 'D')
	{
		fcub->door[*door].pos.x = x;
		fcub->door[*door].pos.y = y;
		fcub->door[*door].in_range = false;
		fcub->door[*door].frame = 0;
		fcub->door[*door].closing = false;
		fcub->door[*door].opening = false;
		fcub->door[*door].animating = false;
		(*door)++;
	}
	else if (fcub->map[y][x] == 'X')
	{
		fcub->exit->pos.x = x;
		fcub->exit->pos.y = y;
		fcub->exit->in_range = false;
		fcub->exit->frame = 0;
		fcub->exit->closing = false;
		fcub->exit->opening = false;
		fcub->exit->animating = false;
	}
}
