/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_flood_fill.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omben-ch <omben-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/13 18:45:07 by omben-ch          #+#    #+#             */
/*   Updated: 2025/09/13 18:46:07 by omben-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_bs.h"

int	get_size_lines_of_map(t_fcub *fcub)
{
	int	x;

	x = 0;
	while (fcub->map[x])
	{
		x++;
	}
	return (x);
}

void	dup_map(t_fcub *fcub, char **map)
{
	int	x;

	x = 0;
	while (fcub->map[x])
	{
		map[x] = ft_strdup(fcub->map[x]);
		if (!map[x])
		{
			free_map_flood_fill(map);
			freeing_data(fcub);
			print_and_exit("error malloc\n");
		}
		x++;
	}
	map[x] = NULL;
}
