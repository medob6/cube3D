/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbousset <mbousset@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 09:35:56 by omben-ch          #+#    #+#             */
/*   Updated: 2025/07/31 10:04:19 by mbousset         ###   ########.fr       */
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
