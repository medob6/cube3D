/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omben-ch <omben-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 15:38:56 by omben-ch          #+#    #+#             */
/*   Updated: 2025/09/01 15:31:30 by omben-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_bs.h"

void	init_data(t_fcub *fcub)
{
	fcub->n_path = NULL;
	fcub->w_path = NULL;
	fcub->e_path = NULL;
	fcub->s_path = NULL;
	fcub->c_color = NULL;
	fcub->f_color = NULL;
	fcub->map = NULL;
}

void	check_name(char *arg)
{
	int	i;

	i = 0;
	if (ft_strlen(arg) < 5)
		print_error_file_and_exit();
	while (arg[i])
		i++;
	if (arg[--i] != 'b' || arg[--i] != 'u' || arg[--i] != 'c'
		|| arg[--i] != '.')
	{
		if (!ft_strcmp(arg, "--rules"))
		{
			print_cub_rules();
			cleanup(0);
		}
		else
			print_error_file_and_exit();
	}
}
int	count_char_in_map(char **map, char c)
{
	int	count;
	int	x;
	int	y;

	x = 0;
	count = 0;
	while (map[x])
	{
		y = 0;
		while (map[x][y])
		{
			if (map[x][y] == c)
				count++;
			y++;
		}
		x++;
	}
	return (count);
}

void	init_door(t_fcub *fcub)
{
	int	size;

	size = count_char_in_map(fcub->map, 'D');
	fcub->door = NULL;
	fcub->nb_door = size;
	if (!size)
		return ;
	fcub->door = malloc(size * sizeof(t_door));
	if (fcub->door == NULL)
	{
		ft_putstr_fd("Malloc error\n", 2);
		cleanup(0);
	}
}

void	get_info_of_door(t_fcub *fcub)
{
	int	door;
	int	x;
	int	y;

	init_door(fcub);
	fcub->exit = malloc(sizeof(t_door));
	door = 0;
	y = 0;
	while (fcub->map[y] && fcub->door)
	{
		x = 0;
		while (fcub->map[y][x])
		{
			if (fcub->map[y][x] == 'D')
			{
				fcub->door[door].pos.x = x;
				fcub->door[door].pos.y = y;
				fcub->door[door].in_range = false;
				fcub->door[door].frame = 0;
				fcub->door[door].closing = false;
				fcub->door[door].opening = false;
				fcub->door[door].animating = false;
				door++;
			}
			else if (fcub->map[y][x] == 'X')
			{


/* FUNCTIONS */

				fcub->exit->pos.x = x;
				fcub->exit->pos.y = y;
				fcub->exit->in_range = false;
				fcub->exit->frame = 0;
				fcub->exit->closing = false;
				fcub->exit->opening = false;
				fcub->exit->animating = false;
			}
			x++;
		}
		y++;
	}
}

void	parse_and_get_data(t_fcub *fcub, int ac, char **av)
{
	int	fd;

	if (ac != 2)
	{
		print_error_argument();
		cleanup(1);
		cleanup(1);
	}
	check_name(av[1]);
	fd = open(av[1], O_RDONLY);
	if (fd == -1)
		print_and_exit(strerror(errno));
	init_data(fcub);
	get_val_of_element(fcub, fd);
	check_content_fc(fcub);
	check_content_map(fcub);
	flood_fill(fcub, get_size_lines_of_map(fcub) + 1,count_line(fcub->map[0]) + 1);
	get_info_of_door(fcub);
}
