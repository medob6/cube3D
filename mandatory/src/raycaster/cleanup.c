#include "cub.h"

void	destroy_image(void *mlx, void *image)
{
	if (image != NULL)
		mlx_destroy_image(mlx, image);
}

void	free_map(char **map, int height)
{
	int	i;

	if (!map)
		return ;
	i = 0;
	while (i < height)
	{
		free(map[i]);
		i++;
	}
	free(map);
}

void	cleanup(t_game *game,int code)
{
	int	i;

	i = 0;
	while (i < 4)
		destroy_image(game->mlx, &game->graphics[i++]);
	destroy_image(game->mlx, &game->display);
	// destroy_image(game->mlx, &game->player.sprite);
	if (game->data.map.arr)
		free_map(game->data.map.arr, game->data.map.map_h);
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