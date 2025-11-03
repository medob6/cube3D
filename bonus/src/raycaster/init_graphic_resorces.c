/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_graphic_resorces.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbousset <mbousset@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 09:14:08 by mbousset          #+#    #+#             */
/*   Updated: 2025/09/18 09:27:43 by mbousset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_bs.h"

void	init_videos(void)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		get_game()->videos[i].active = false;
		get_game()->videos[i].played = false;
		get_game()->videos[i].result = 0;
		i++;
	}
}

void	part_one(t_game *game)
{
	init_image(game, &game->graphic_menu[BG_IMG], "bonus/textures/bg.xpm");
	init_image(game, &game->graphic_menu[START_IMG],
		"bonus/textures/start.xpm");
	init_image(game, &game->graphic_menu[CONTROL_IMG],
		"bonus/textures/control.xpm");
	init_image(game, &game->graphic_menu[EXIT_IMG], "bonus/textures/exit.xpm");
	init_image(game, &game->graphic_menu[H_START_IMG],
		"bonus/textures/h_start.xpm");
	init_image(game, &game->graphic_menu[H_CONTROL_IMG],
		"bonus/textures/h_control.xpm");
	init_image(game, &game->graphic_menu[H_EXIT_IMG],
		"bonus/textures/h_exit.xpm");
	init_image(game, &game->graphic_menu[CONTROL_PAGE_IMG],
		"bonus/textures/control_page.xpm");
}

void	part_two(t_game *game)
{
	init_image(game, &game->graphic_menu[EXIT_PAGE_IMG],
		"bonus/textures/exit_page.xpm");
	init_image(game, &game->graphic_menu[NO_IMG], "bonus/textures/no.xpm");
	init_image(game, &game->graphic_menu[YES_IMG], "bonus/textures/yes.xpm");
	init_image(game, &game->graphic_menu[H_NO_IMG], "bonus/textures/h_no.xpm");
	init_image(game, &game->graphic_menu[H_YES_IMG],
		"bonus/textures/h_yes.xpm");
	init_image(game, &game->graphic_menu[RETURN_IMG],
		"bonus/textures/return.xpm");
	init_image(game, &game->graphic_menu[H_RETURN_IMG],
		"bonus/textures/h_return.xpm");
	init_image(game, &game->graphic_menu[NUMBERS_IMG],
		"bonus/textures/numbers.xpm");
	init_image(game, &game->graphic_menu[POINT_IMG],
		"bonus/textures/2_point.xpm");
	init_image(game, &game->graphic_menu[TIMER_BG_IMG],
		"bonus/textures/timer_bg.xpm");
}

void	initilize_menu_images(t_game *game)
{
	part_one(game);
	part_two(game);
}

void	initilize_game_resorces(t_game *game)
{
	init_videos();
	init_keys(game);
	init_player(game);
	init_image_fram(game, &game->display);
	init_image(game, &game->graphics[E_WALL], game->data.paths[E_WALL]);
	init_image(game, &game->graphics[N_WALL], game->data.paths[N_WALL]);
	init_image(game, &game->graphics[W_WALL], game->data.paths[W_WALL]);
	init_image(game, &game->graphics[S_WALL], game->data.paths[S_WALL]);
	init_image(game, &game->graphics[DOOR], "bonus/textures/door.xpm");
	game->graphics[DOOR].frames = 10;
	init_image(game, &game->graphics[N_ICONE], "bonus/textures/N_icon.xpm");
	init_image(game, &game->graphics[ARROW],
		"bonus/textures/minimap_player.xpm");
	init_image(game, &game->graphics[PORTAL], "bonus/textures/portal.xpm");
	game->graphics[PORTAL].frames = 32;
	init_image2(game, &game->graphics[FLOOR], "bonus/textures/floor.xpm");
	init_image2(game, &game->graphics[SKY], "bonus/textures/sky.xpm");
	initilize_menu_images(game);
	init_timer_pic(game);
}
