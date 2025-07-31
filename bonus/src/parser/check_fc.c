/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_fc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbousset <mbousset@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 09:38:42 by omben-ch          #+#    #+#             */
/*   Updated: 2025/07/31 10:04:19 by mbousset         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub_bs.h"

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
		print_error_argument();
		return (1);
	}
	i = -1;
	while (++i < 3)
	{
		if (!check_nb_is_valide(list[i]))
		{
			freeing_list(list);
			print_error_argument();
			return (1);
		}
	}
	freeing_list(list);
	return (0);
}

void	check_content_fc(t_fcub *fcub)
{
	if (check_val_of_fc(fcub->f_color) || check_val_of_fc(fcub->c_color))
	{
		freeing_data(fcub);
		cleanup(1);
	}
}
