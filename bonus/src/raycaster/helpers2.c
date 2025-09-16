/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbousset <mbousset@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 16:07:10 by mbousset          #+#    #+#             */
/*   Updated: 2025/09/16 09:55:31 by mbousset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycaster_bs.h"

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

void	fill_line_inf(t_sec *line, int dir, double wall_x, double dist)
{
	line->dir = dir;
	line->wall_x = wall_x;
	line->raw_dist = dist;
}

bool	in_minimap_range(int w_x)
{
	int	minimap_r;
	int	minima_c;
	int	var;

	minimap_r = get_game()->win_h * MINIMAP_SCREEN_SCALE;
	minima_c = minimap_r * 1.2;
	var = minimap_r + minimap_r * ICON_SCALE * 2;
	if (w_x < minima_c + var && w_x > minima_c - var)
		return (true);
	return (false);
}
