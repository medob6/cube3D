/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbousset <mbousset@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/20 09:38:33 by omben-ch          #+#    #+#             */
/*   Updated: 2025/06/27 11:18:41 by mbousset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

// void	print_map(t_map *map)
// {
// 	int	i;

// 	i = 0;
// 	while (i < map->map_h)
// 	{
// 		printf("%s\n", map->arr[i++]);
// 	}
// }

int get_rgb(t_fcub *fcub, char *color)
{
	char **list;
	int rgb[3];

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

void	parse_input(t_game *game, int ac, char **av)
{
	t_fcub fcub;
	
	parse_and_get_data(&fcub,ac,av);
	game->data.paths[N_WALL] = fcub.n_path;
	game->data.paths[W_WALL] = fcub.w_path;
	game->data.paths[E_WALL] = fcub.e_path;
	game->data.paths[S_WALL] = fcub.s_path;
	game->data.ceiling_clr = get_rgb(&fcub, fcub.c_color);
	game->data.floor_clr = get_rgb(&fcub, fcub.f_color);
	game->data.map.arr = fcub.map;
	game->data.map.map_h = count_list(fcub.map);
	game->data.map.map_w = get_size_of_long_line(&fcub);
}

void	print_err(char *msg)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(msg, 2);
	cleanup(EXIT_FAILURE);
}

int	game_loop(t_game *game)
{
	update_player(game);
	game->player.moving = true;
	if (game->player.moving)
	{
		// cast_rays(game);
		// draw_3d_view(game);
		draw_mini_map(game);
		// draw_player(game);
	}
	mlx_put_image_to_window(game->mlx, game->win, game->display.img, 0, 0);
	return (1);
}

void	lunch_game_hooks(t_game *game)
{
	mlx_do_key_autorepeatoff(game->mlx);
	mlx_hook(game->win, 2, 1L << 0, key_press, game);
	mlx_hook(game->win, 3, 1L << 1, key_release, game);
	mlx_loop_hook(game->mlx, game_loop, game);
	mlx_loop(game->mlx);
}

int	main(int ac, char **av)
{
	t_game	*game;

	game = get_game();
	game->mlx = mlx_init();
	if (!game->mlx)
		print_err("Failed to initialize MLX\n");
	get_window_dimensions();
	parse_input(game, ac, av);
	game->win = mlx_new_window(game->mlx, game->win_w, game->win_h, "Cub3D");
	if (!game->win)
		print_err("Failed to create window\n");
	
	initilize_game_resorces(game);
	lunch_game_hooks(game);
	return (0);
}
