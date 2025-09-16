/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_resorces.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbousset <mbousset@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 15:39:37 by mbousset          #+#    #+#             */
/*   Updated: 2025/09/16 09:18:26 by mbousset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_bs.h"

void	init_image_fram(t_game *game, t_image *frame)
{
	frame->img = mlx_new_image(game->mlx, game->win_w, game->win_h);
	if (!frame->img)
		print_err("Failed to create image");
	frame->addr = mlx_get_data_addr(frame->img, &frame->bpp, &frame->line_len,
			&frame->endian);
	if (!frame->addr)
		print_err("Failed to get image data address");
}

void	init_image(t_game *game, t_image *img, char *path)
{
	img->img = mlx_xpm_file_to_image(game->mlx, path, &img->w, &img->h);
	if (!img->img)
	{
		perror("Error: Failed to load an image ");
		cleanup(1);
	}
	img->addr = mlx_get_data_addr(img->img, &img->bpp, &img->line_len,
			&img->endian);
	img->frames = 1;
}

void	init_player(t_game *game)
{
	int		y;
	int		x;
	char	**map;

	map = game->data.map.arr;
	game->player.moving = false;
	y = -1;
	while (map[++y])
	{
		x = -1;
		while (map[y][++x])
		{
			if (is_valid_dir(map[y][x]))
			{
				game->player.p.x = (x + 0.5) * WALL_WIDTH;
				game->player.p.y = (y + 0.5) * WALL_WIDTH;
				game->player.p.z = 0;
				game->player.angle = get_view_angel(map[y][x]);
				game->player.moving = true;
				map[y][x] = '0';
				game->player_info = game->player;
				return ;
			}
		}
	}
}
