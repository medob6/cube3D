/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbousset <mbousset@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 15:39:33 by mbousset          #+#    #+#             */
/*   Updated: 2025/06/25 15:39:34 by mbousset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	destroy_image(void *mlx, void *image)
{
	if (image != NULL)
		mlx_destroy_image(mlx, image);
}

void	free_map(t_map *map)
{
	int	i;

	if (!map)
		return ;
	i = 0;
	while (i < map->map_h)
	{
		free(map->arr[i]);
		i++;
	}
	free(map->arr);
}

void	cleanup(t_game *game,int code)
{
	int	i;

	i = 0;
	while (i < 6)
		destroy_image(game->mlx, game->graphics[i++].img);
	destroy_image(game->mlx, game->display.img);
	// destroy_image(game->mlx, &game->player.sprite);
	if (game->data.map.arr)
		free_map(&game->data.map);
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
	exit(code);
}

int	handle_close(t_game *game)
{
	write(1, "Window closed.\n", 15);
	if (game->mlx && game->win)
		mlx_destroy_window(game->mlx, game->win);
	cleanup(game,EXIT_SUCCESS);
	return (0);
}