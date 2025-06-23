/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sum_checks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omben-ch <omben-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/15 15:27:03 by omben-ch          #+#    #+#             */
/*   Updated: 2025/06/23 08:03:04 by omben-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	check_and_get_val(t_data *data, char **list)
{
	if ((!ft_strcmp("N", list[0]) || !ft_strcmp("NO", list[0]))
		&& !data->n_path)
		data->n_path = ft_strdup(list[1]);
	else if ((!ft_strcmp("S", list[0]) || !ft_strcmp("SO", list[0]))
		&& !data->s_path)
		data->s_path = ft_strdup(list[1]);
	else if ((!ft_strcmp("W", list[0]) || !ft_strcmp("WE", list[0]))
		&& !data->w_path)
		data->w_path = ft_strdup(list[1]);
	else if ((!ft_strcmp("E", list[0]) || !ft_strcmp("EA", list[0]))
		&& !data->e_path)
		data->e_path = ft_strdup(list[1]);
	else if (!ft_strcmp("F", list[0]) && !data->f_color)
		data->f_color = ft_strdup(list[1]);
	else if (!ft_strcmp("C", list[0]) && !data->c_color)
		data->c_color = ft_strdup(list[1]);
	else
		return (1);
	return (0);
}

int	check_element_name(t_data *data, char *line)
{
	char	**list;

	list = ft_split(line, " \t\n");
	if (!list)
		return (1);
	if (nb_args(list) > 2)
		return (1); //! freeing list
	if (check_and_get_val(data, list))
		return (1); //! freeing list
	//! freeing list
	return (0);
}

int	check_val_data(t_data *data)
{
	if (!data->n_path || !data->w_path || !data->e_path || !data->s_path
		|| !data->f_color || !data->c_color)
		return (1);
	return (0);
}

int	get_val_nwesfc(t_data *data, int fd)
{
	char	*line;

	line = NULL;
	while (check_val_data(data))
	{
		line = get_next_line(fd);
		if (!line)
		{
			free(line);
			print_error_map("1- error EOF");
		}
		if (line[0] != '\n' && check_element_name(data, line))
		{
			free(line);
			return (1);
		}
		free(line);
	}
	return (0);
}

int count_arg(char **map)
{
	int i;

	i = 0;
	while (map && map[i])
		i++;
	return (i);
}

int	set_line_map(t_data *data, char *line)
{
	char	**list;
	char	**tmp;
	int size;
	int i;

	size = count_arg(data->map);
	if (!size)
	{
		data->map = (char **)malloc(2 * sizeof(char *));
		if (!data->map)
			return (1);
		data->map[0] = ft_strdup(line);
		data->map[1] = NULL;
	}
	else
	{
		list = (char **)malloc((size + 2) * sizeof(char *));
		tmp = data->map;
		data->map = list;
		i = 0;
		while (tmp[i])
		{
			data->map[i] = tmp[i];
			i++;
		}
		data->map[i++] = ft_strdup(line);
		data->map[i] = NULL;
		//! freeing tmp
 	}
	return (0);
}

int	get_val_map(t_data *data, int fd)
{
	char	*line;

	line = NULL;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break;
		if (line[0] != '\n' && set_line_map(data, line))
		{
			free(line);
			return (1);
		}
		if (line[0] == '\n' && data->map)
		{
			free(line);
			return (1);
		}
		free(line);
	}
	return (0);
}

void sup_newline(t_data *data)
{
	char **tmp_list;
	int i;
	
	i = 0;
	while (data->map[i])
	{
		tmp_list = ft_split(data->map[i] , "\n");
		if (!tmp_list)
			exit(1);//! freeing data
		free(data->map[i]);
		free(tmp_list[1]);
		data->map[i] = tmp_list[0];
		free(tmp_list);
		i++;
	}
}

void	get_val_element(t_data *data, int fd)
{
	if (get_val_nwesfc(data, fd) || get_val_map(data, fd))
	{
		//! freeing struct of data
		printf("error nwfc or in map \n");
		exit(1);
	}
	sup_newline(data);
}

// check_nswe(fd);
// check_fc(check_newline(fd), fd);
// check_content_map(check_newline(fd), fd, file_name);
// check_newline(fd);
// check_content_map(fd, tmp_fd);
// close(fd);
// close(tmp_fd);