/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_fc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omben-ch <omben-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 09:38:42 by omben-ch          #+#    #+#             */
/*   Updated: 2025/06/23 15:14:31 by omben-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int check_diget_comma(char *arg)
{
    int i;
    int j;
    
    i = 0;
    j = 0;
    while (arg[i] && arg[i] != '\n')
    {
        if (!(arg[i] >= '0' && arg[i] <= '9') && arg[i] != ',')
            return (1);
        if (arg[i] == ',')
            j++;
        i++;
    }
    if (j > 2)
        return (1);
    return (0);
}

int	check_nb_is_valide(const char *str)
{
	int                 nb;
	int					sign;
	int					i;

	nb = 0;
	sign = 1;
	i = 0;
	while ((str[i] >= '0' && str[i] <= '9'))
	{
		nb = nb * 10 + str[i] - '0';
		if (nb > 255)
            return (0);
		i++;
	}
    if (str[i] != '\n' && str[i])
	    return (1);
	return (1);
}

// int check_nb_args(char **args)
// {
//     int i;
    
//     i = 0;
//     if (!args)
//     {
//         printf("1- error malloc\n");    
//         return (1);
//     }
//     while (args[i])
//         i++;
//     if (i != 3)
//     {
//         i = 0;
//         while (args[i])
//             free(args[i++]);
//         free(args); 
//         print_error_map("1- error 3 nb not existe");    
//     }
//     return (0);
// }

void free_list(char **args)
{
    int i;

    i = 0;
    while (args[i])
        free(args[i++]);
    free(args);
}

int check_val(char *arg)
{
    char **args;
    int i;
    int j;

    i = 0;
    j = 0;
    if (check_diget_comma(arg))
        return (1);
    args = ft_split(arg, ",");
    if (nb_args(args) != 3)
    {
        free_list(args);
        printf("1- error nb args\n");    
        return (1);
    }
    i = -1;
    while (++i < 3)
    {
        if (!check_nb_is_valide(args[i]))
            j = 1;
    }
    free_list(args);
    if (j)
        printf("1- error nb args\n");
    return (0);
}

void check_content_fc(t_data *data)
{
    if (check_val(data->f_color) || check_val(data->c_color))
    {
		//! freeing struct of data
        printf("error fc val \n");
		exit(1);
	}
}
