/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_val_of_file.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omben-ch <omben-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 15:27:03 by omben-ch          #+#    #+#             */
/*   Updated: 2025/09/15 16:40:40 by omben-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_bs.h"

int	check_and_get_val(t_fcub *fcub, char **list)
{
	if ((!ft_strcmp("N", list[0]) || !ft_strcmp("NO", list[0]))
		&& !fcub->n_path)
		fcub->n_path = ft_strdup(list[1]);
	else if ((!ft_strcmp("S", list[0]) || !ft_strcmp("SO", list[0]))
		&& !fcub->s_path)
		fcub->s_path = ft_strdup(list[1]);
	else if ((!ft_strcmp("W", list[0]) || !ft_strcmp("WE", list[0]))
		&& !fcub->w_path)
		fcub->w_path = ft_strdup(list[1]);
	else if ((!ft_strcmp("E", list[0]) || !ft_strcmp("EA", list[0]))
		&& !fcub->e_path)
		fcub->e_path = ft_strdup(list[1]);
	else if (!ft_strcmp("F", list[0]) && !fcub->f_color)
		fcub->f_color = ft_strdup(list[1]);
	else if (!ft_strcmp("C", list[0]) && !fcub->c_color)
		fcub->c_color = ft_strdup(list[1]);
	else
		return (1);
	return (0);
}

int	get_val_nwesfc(t_fcub *fcub, int fd)
{
	char	*line;

	line = NULL;
	while (check_struct_fcub_val(fcub))
	{
		line = get_next_line(fd);
		if (!line)
		{
			free(line);
			print_error_argument("North or South or East or West or Floor or Ceiling");
			return (1);
		}
		if (line[0] != '\n' && check_nwesfc(fcub, line))
		{
			free(line);
			print_error_argument("North or South or East or West or Floor or Ceiling");
			return (1);
		}
		free(line);
	}
	return (0);
}

int	set_line_map(t_fcub *fcub, char *line, int size_of_map)
{
	char	**list;
	char	**tmp;
	int		i;

	if (!size_of_map)
	{
		if (add_val(fcub, line))
			return (1);
	}
	else
	{
		list = (char **)malloc((size_of_map + 2) * sizeof(char *));
		if (!list)
			return (1);
		tmp = fcub->map;
		fcub->map = list;
		i = -1;
		while (tmp[++i])
			fcub->map[i] = tmp[i];
		fcub->map[i++] = ft_strdup(line);
		fcub->map[i] = NULL;
		free(tmp);
	}
	return (0);
}

int	get_val_map(t_fcub *fcub, int fd)
{
	char	*line;

	line = NULL;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (line[0] != '\n' && set_line_map(fcub, line, count_list(fcub->map)))
		{
			print_error_argument("Map");
			free(line);
			return (1);
		}
		if (line[0] == '\n' && fcub->map)
		{
			print_error_argument("Map");
			free(line);
			return (1);
		}
		free(line);
	}
	return (0);
}

void	get_val_of_element(t_fcub *fcub, int fd)
{
	if (get_val_nwesfc(fcub, fd) || get_val_map(fcub, fd))
	{
		freeing_data(fcub);
		cleanup(1);
	}
	if (check_struct_fcub_val(fcub))
	{
		print_error_argument("North or South or East or West or Floor or Ceiling");
		freeing_data(fcub);
		cleanup(1);
	}
	if (!fcub->map)
	{
		print_error_argument("Map");
		freeing_data(fcub);
		cleanup(1);
	}
	sup_newline(fcub);
}
