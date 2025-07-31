/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbousset <mbousset@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 16:07:10 by mbousset          #+#    #+#             */
/*   Updated: 2025/07/31 10:04:19 by mbousset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_bs.h"

double	pow_2(double n)
{
	return (n * n);
}

int	get_rgb(t_fcub *fcub, char *color)
{
	char	**list;
	int		rgb[3];

	list = ft_split(color, ",");
	if (!list)
	{
		freeing_data(fcub);
		print_and_exit("error malloc\n");
	}
	rgb[0] = ft_atoi((const char *)list[0]);
	rgb[1] = ft_atoi((const char *)list[1]);
	rgb[2] = ft_atoi((const char *)list[2]);
	freeing_list(list);
	free(color);
	return (rgb[0] << 16 | rgb[1] << 8 | rgb[2]);
}

void	handle_exit(t_game *game)
{
	if (get_key(KEY_ESCAPE, game)->press)
		handle_close();
}
