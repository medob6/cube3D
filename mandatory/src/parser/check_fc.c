/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_fc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omben-ch <omben-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 09:38:42 by omben-ch          #+#    #+#             */
/*   Updated: 2025/06/25 09:58:35 by omben-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int check_diget_comma(char *arg)
{
    int i;
    int j;
    
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
        ft_putstr_fd("error more comma\n", 2);
        return (1);
    }
    return (0);
}

int	check_nb_is_valide(const char *str)
{
	int                 nb;
	int					i;

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

int check_val(char *arg)
{
    char **args;
    int i;
    int j;

    i = 0;
    j = 0;
    if (check_diget_comma(arg))
    {
        ft_putstr_fd("error format\n", 2);
        return (1);
    }
    args = ft_split(arg, ",");
    if (!args)
    {
        ft_putstr_fd("error malloc\n", 2);
        return (1);
    }
    if (nb_args(args) != 3)
    {
        freeing_list(args);
        ft_putstr_fd("error nb args\n", 2);
        return (1);
    }
    i = -1;
    while (++i < 3)
    {
        if (!check_nb_is_valide(args[i]))
        {
            freeing_list(args);
            ft_putstr_fd("error nb args\n", 2);
            return (1);
        }
    }
    freeing_list(args);
    return (0);
}

void check_content_fc(t_data *data)
{
    if (check_val(data->f_color))
    {
        freeing_data(data);
		exit(1);
	}
    if (check_val(data->c_color))
    {
        freeing_data(data);
		exit(1);
	}
}
