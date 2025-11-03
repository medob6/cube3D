/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omben-ch <omben-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/26 15:17:02 by omben-ch          #+#    #+#             */
/*   Updated: 2025/09/16 14:47:29 by omben-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_bs.h"

int	check_struct_fcub_val(t_fcub *fcub)
{
	if (!fcub->n_path || !fcub->w_path || !fcub->e_path || !fcub->s_path
		|| !fcub->f_color || !fcub->c_color)
		return (1);
	return (0);
}

void	sup_newline(t_fcub *fcub)
{
	char	**tmp_list;
	int		i;

	i = 0;
	while (fcub->map[i])
	{
		tmp_list = ft_split(fcub->map[i], "\n");
		if (!tmp_list)
		{
			print_error_argument("error maloc");
			freeing_data(fcub);
			cleanup(1);
		}
		free(fcub->map[i]);
		free(tmp_list[1]);
		fcub->map[i] = tmp_list[0];
		free(tmp_list);
		i++;
	}
}

int	add_val(t_fcub *fcub, char *line)
{
	fcub->map = (char **)malloc(2 * sizeof(char *));
	if (!fcub->map)
		return (1);
	fcub->map[0] = ft_strdup(line);
	fcub->map[1] = NULL;
	return (0);
}

int	check_nwesfc(t_fcub *fcub, char *line)
{
	char	**list;

	list = ft_split(line, " \t\n");
	if (!list)
		return (1);
	if (count_list(list) > 2)
	{
		freeing_list(list);
		return (1);
	}
	if (check_and_get_val(fcub, list))
	{
		freeing_list(list);
		return (1);
	}
	freeing_list(list);
	return (0);
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
