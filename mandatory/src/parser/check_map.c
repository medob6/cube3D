/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_content_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omben-ch <omben-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 16:57:04 by omben-ch          #+#    #+#             */
/*   Updated: 2025/06/21 16:08:32 by omben-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	counter_line(char *str)
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

void	print_error_map_and_exit(t_data *data)
{
	ft_putstr_fd("error line map\n", 2);
	freeing_data(data);
	exit(1);
}

void	check_line_first_last(t_data *data, int last_line)
{
	int	i;

	i = 0;
	while (data->map[0][i])
	{
		if (!ft_strchr("1 ", data->map[0][i]))
			print_error_map_and_exit(data);
		i++;
	}
	i = 0;
	while (data->map[last_line][i])
	{
		if (!ft_strchr("1 ", data->map[last_line][i]))
			print_error_map_and_exit(data);
		i++;
	}
}

int	get_size_of_long_line(t_data *data)
{
	int	i;
	int	size_line;
	int	tmp_size_line;

	i = 0;
	size_line = 0;
	while (data->map[i])
	{
		tmp_size_line = counter_line(data->map[i]);
		if (tmp_size_line == -1)
		{
			ft_putstr_fd("the line is solong\n", 2);
			freeing_data(data);
			exit(1);
		}
		if (tmp_size_line > size_line)
			size_line = tmp_size_line;
		i++;
	}
	return (size_line);
}

void	add_space(t_data *data)
{
	char	*tmp;
	char	*tmp_two;
	int		size_line;
	int		nb_space;
	int		i;

	i = -1;
	size_line = get_size_of_long_line(data);
	while (data->map[++i])
	{
		nb_space = size_line - counter_line(data->map[i]);
		while (nb_space--)
		{
			tmp = data->map[i];
			tmp_two = ft_strjoin(data->map[i], " ");
			if (!tmp_two)
			{
				freeing_data(data);
				ft_putstr_fd("error malloc\n", 2);
				exit(1);
			}
			data->map[i] = tmp_two;
			free(tmp);
		}
	}
}

void	position_of_plaer_and_floor_check(t_data *data, char **map, int x,
		int y)
{
	if (x && map[x][y] && map[x + 1] && ft_strchr("0NWSE", map[x][y])
		&& (!ft_strchr("10NWSE", map[x][y - 1]) || !ft_strchr("10NWSE", map[x][y
				+ 1]) || !ft_strchr("10NWSE", map[x - 1][y])
			|| !ft_strchr("10NWSE", map[x + 1][y])))
		print_error_map_and_exit(data);
}

void	check_content_map(t_data *data)
{
	int	x;
	int	y;
	int	position;

	x = 0;
	position = 0;
	add_space(data);
	check_line_first_last(data, nb_args(data->map) - 1);
	while (data->map[++x] && data->map[x + 1])
	{
		y = -1;
		while (data->map[x][++y])
		{
			if (!ft_strchr(" 10NWSE", data->map[x][y]))
				print_error_map_and_exit(data);
			if (!ft_strchr(" 10NWSE", data->map[x][y]))
				print_error_map_and_exit(data);
			position_of_plaer_and_floor_check(data, data->map, x, y);
			if (ft_strchr("NWSE", data->map[x][y]))
				position++;
		}
	}
	if (position != 1)
		print_error_map_and_exit(data);
}
