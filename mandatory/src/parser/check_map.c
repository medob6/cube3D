/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omben-ch <omben-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 15:14:23 by omben-ch          #+#    #+#             */
/*   Updated: 2025/07/13 10:03:18 by omben-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	add_space(t_fcub *fcub)
{
	char	*tmp;
	char	*tmp_two;
	int		size_line;
	int		nb_space;
	int		i;

	i = -1;
	size_line = get_size_of_long_line(fcub);
	while (fcub->map[++i])
	{
		nb_space = size_line - count_line(fcub->map[i]);
		while (nb_space--)
		{
			tmp = fcub->map[i];
			tmp_two = ft_strjoin(fcub->map[i], " ");
			if (!tmp_two)
			{
				freeing_data(fcub);
				print_error_argument();
				cleanup(1);
			}
			fcub->map[i] = tmp_two;
			free(tmp);
		}
	}
}

void	check_line_first_last(t_fcub *fcub, int last_line)
{
	int	i;

	i = 0;
	while (fcub->map[0][i])
	{
		if (!ft_strchr("1 ", fcub->map[0][i]))
			print_error_map_and_exit(fcub);
		i++;
	}
	i = 0;
	while (fcub->map[last_line][i])
	{
		if (!ft_strchr("1 ", fcub->map[last_line][i]))
			print_error_map_and_exit(fcub);
		i++;
	}
}

int	get_size_of_long_line(t_fcub *fcub)
{
	int	i;
	int	size_line;
	int	tmp_size_line;

	i = 0;
	size_line = 0;
	while (fcub->map[i])
	{
		tmp_size_line = count_line(fcub->map[i]);
		if (tmp_size_line == -1)
		{
			print_error_argument();
			freeing_data(fcub);
			cleanup(1);
		}
		if (tmp_size_line > size_line)
			size_line = tmp_size_line;
		i++;
	}
	return (size_line);
}

void	position_of_player_and_floor_check(t_fcub *fcub, char **map, int x,
		int y)
{
	if ((!y && ft_strchr("0NWSE", map[x][y])) || (ft_strchr("0NWSE", map[x][y]) && !map[x][y + 1]))
		print_error_map_and_exit(fcub);
	if (x && map[x][y] && map[x + 1] && ft_strchr("0NWSE", map[x][y])
		&& (!ft_strchr("10NWSE", map[x][y - 1]) || !ft_strchr("10NWSE", map[x][y
				+ 1]) || !ft_strchr("10NWSE", map[x - 1][y])
			|| !ft_strchr("10NWSE", map[x + 1][y])))
		print_error_map_and_exit(fcub);
}

void	check_content_map(t_fcub *fcub)
{
	int	x;
	int	y;
	int	position;

	x = 0;
	position = 0;
	add_space(fcub);
	check_line_first_last(fcub, count_list(fcub->map) - 1);
	while (fcub->map[++x] && fcub->map[x + 1])
	{
		y = -1;
		while (fcub->map[x][++y])
		{
			if (!ft_strchr(" 10NWSE", fcub->map[x][y]))
				print_error_map_and_exit(fcub);
			position_of_player_and_floor_check(fcub, fcub->map, x, y);
			if (ft_strchr("NWSE", fcub->map[x][y]))
				position++;
		}
	}
	if (position != 1)
		print_error_map_and_exit(fcub);
}
