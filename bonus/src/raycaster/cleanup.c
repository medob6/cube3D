/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omben-ch <omben-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 15:39:33 by mbousset          #+#    #+#             */
/*   Updated: 2025/09/18 18:49:43 by omben-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_bs.h"
#include "raycaster_bs.h"
#include "video_bs.h"

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

void	next_freeing(t_game *game)
{
	free(game->data.paths[0]);
	free(game->data.paths[1]);
	free(game->data.paths[2]);
	free(game->data.paths[3]);
	free(game->doors);
	display_scean(game, true);
	play_video("NULL", true);
}

void	cleanup(int code)
{
	int		i;
	t_game	*game;

	game = get_game();
	i = 0;
	if (game->mlx && game->win)
		mlx_destroy_window(game->mlx, game->win);
	while (i < NB_GRAGHICS)
		destroy_image(game->mlx, game->graphics[i++].img);
	destroy_image(game->mlx, game->display.img);
	destroy_image(game->mlx, game->img_timer.img);
	next_freeing(game);
	i = 0;
	while (i < NB_IMG_MENU)
		destroy_image(game->mlx, game->graphic_menu[i++].img);
	if (game->data.map.arr)
		free_map(&game->data.map);
	if (game->mlx)
	{
		mlx_do_key_autorepeaton(game->mlx);
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
	exit(code);
}

int	handle_close(void)
{
	write(1, "Window closed.\n", 15);
	cleanup(EXIT_SUCCESS);
	return (0);
}
