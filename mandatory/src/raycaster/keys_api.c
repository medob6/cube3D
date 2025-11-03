/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys_api.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omben-ch <omben-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 15:40:06 by mbousset          #+#    #+#             */
/*   Updated: 2025/09/16 16:15:35 by omben-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

t_key	*get_key(int keycode, t_game *game)
{
	int	i;

	i = 0;
	while (i < 10)
	{
		if (game->keys[i].code == keycode)
			return (&game->keys[i]);
		i++;
	}
	return (NULL);
}

int	key_press(int keycode, t_game *game)
{
	t_key	*k;

	k = get_key(keycode, game);
	if (k)
		k->press = true;
	return (0);
}

int	key_release(int keycode, t_game *game)
{
	t_key	*k;

	k = get_key(keycode, game);
	if (k)
		k->press = false;
	return (0);
}

void	init_keys(t_game *game)
{
	game->keys[0] = (t_key){KEY_ESCAPE, false};
	game->keys[1] = (t_key){KEY_UP, false};
	game->keys[2] = (t_key){KEY_DOWN, false};
	game->keys[3] = (t_key){KEY_LEFT, false};
	game->keys[4] = (t_key){KEY_RIGHT, false};
	game->keys[5] = (t_key){ARROW_UP, false};
	game->keys[6] = (t_key){ARROW_DOWN, false};
	game->keys[7] = (t_key){ARROW_LEFT, false};
	game->keys[8] = (t_key){ARROW_RIGHT, false};
	game->keys[9] = (t_key){KEY_SPACE, false};
	game->keys[10] = (t_key){KEY_O, false};
}
