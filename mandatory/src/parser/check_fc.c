/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_fc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omben-ch <omben-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 09:38:42 by omben-ch          #+#    #+#             */
/*   Updated: 2025/09/15 16:36:19 by omben-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	check_diget_and_comma(char *arg)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (arg[i])
	{
		if (!(arg[i] >= '0' && arg[i] <= '9') && arg[i] != ',')
			return (1);
		if (arg[i] == ',')
			j++;
		i++;
	}
	if (j != 2)
	{
		return (1);
	}
	return (0);
}

int	check_nb_is_valide(const char *str)
{
	int	nb;
	int	i;

	nb = 0;
	i = 0;
	while ((str[i] >= '0' && str[i] <= '9'))
	{
		nb = nb * 10 + str[i] - '0';
		if (nb > 255)
			return (0);
		i++;
	}
	if (str[i])
		return (0);
	return (1);
}

int	check_val_of_fc(char *arg)
{
	char	**list;
	int		i;

	list = NULL;
	list = ft_split(arg, ",");
	if (check_diget_and_comma(arg) || !list || count_list(list) != 3)
	{
		freeing_list(list);
		return (1);
	}
	i = -1;
	while (++i < 3)
	{
		if (!check_nb_is_valide(list[i]))
		{
			freeing_list(list);
			return (1);
		}
	}
	freeing_list(list);
	return (0);
}

void	check_content_fc(t_fcub *fcub)
{
	if (check_val_of_fc(fcub->f_color))
	{
		print_error_argument("Floor");
		freeing_data(fcub);
		cleanup(1);
	}
	if (check_val_of_fc(fcub->c_color))
	{
		print_error_argument("Ceiling");
		freeing_data(fcub);
		cleanup(1);
	}
}
