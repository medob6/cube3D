/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_resorces.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omben-ch <omben-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 15:39:37 by mbousset          #+#    #+#             */
/*   Updated: 2025/09/01 15:33:50 by omben-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_bs.h"

double	get_view_angel(char dir)
{
	if (dir == 'E')
		return (deg_to_rad(0));
	else if (dir == 'S')
		return (deg_to_rad(90));
	else if (dir == 'W')
		return (deg_to_rad(180));
	else if (dir == 'N')
		return (deg_to_rad(270));
	return (1);
}

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
	y = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (is_valid_dir(map[y][x]))
			{
				game->player.p.x = (x + 0.5) * WALL_WIDTH;
				game->player.p.y = (y + 0.5) * WALL_WIDTH;
				game->player.p.z = 0;
				game->player.angle = get_view_angel(map[y][x]);
				game->player.moving = true;
				map[y][x] = '0';
				return ;
			}
			x++;
		}
		y++;
	}
}

void	initilize_game_resorces(t_game *game)
{
	// if (SDL_Init(SDL_INIT_AUDIO) < 0)
	// 	return ;
	init_keys(game);
	init_player(game);
	init_image_fram(game, &game->display);
	init_image(game, &game->graphics[E_WALL], game->data.paths[E_WALL]);
	init_image(game, &game->graphics[N_WALL], game->data.paths[N_WALL]);
	init_image(game, &game->graphics[W_WALL], game->data.paths[W_WALL]);
	init_image(game, &game->graphics[S_WALL], game->data.paths[S_WALL]);
	init_image(game, &game->graphics[DOOR], "bonus/textures/door.xpm");
	// draw_vert_line(&game->graphics[DOOR], (164) ,game->graphics[DOOR].h);
	// draw_vert_line(&game->graphics[DOOR], (game->graphics[DOOR].w /3  * 2) ,game->graphics[DOOR].w);
	game->graphics[DOOR].frames = 10;
	init_image(game, &game->graphics[N_ICONE], "bonus/textures/N_icon.xpm");
	init_image(game, &game->graphics[ARROW],
		"bonus/textures/minimap_player.xpm");
	init_image(game, &game->graphics[PORTAL], "bonus/textures/portal.xpm");
	game->graphics[PORTAL].frames = 10;
	init_image(game, &game->graphic_menu[BG_IMG],
		"bonus/textures/bg.xpm");
	init_image(game, &game->graphic_menu[START_IMG],
		"bonus/textures/start.xpm");
	init_image(game, &game->graphic_menu[CONTROL_IMG],
		"bonus/textures/control.xpm");
	init_image(game, &game->graphic_menu[EXIT_IMG],
		"bonus/textures/exit.xpm");
	init_image(game, &game->graphic_menu[H_START_IMG],
		"bonus/textures/h_start.xpm");
	init_image(game, &game->graphic_menu[H_CONTROL_IMG],
		"bonus/textures/h_control.xpm");
	init_image(game, &game->graphic_menu[H_EXIT_IMG],
		"bonus/textures/h_exit.xpm");
	init_image(game, &game->graphic_menu[CONTROL_PAGE_IMG],
		"bonus/textures/control_page.xpm");
	init_image(game, &game->graphic_menu[EXIT_PAGE_IMG],
		"bonus/textures/exit_page.xpm");
	init_image(game, &game->graphic_menu[NO_IMG],
		"bonus/textures/no.xpm");
	init_image(game, &game->graphic_menu[YES_IMG],
		"bonus/textures/yes.xpm");
	init_image(game, &game->graphic_menu[H_NO_IMG],
		"bonus/textures/h_no.xpm");
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
