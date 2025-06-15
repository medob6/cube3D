/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omben-ch <omben-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 15:38:56 by omben-ch          #+#    #+#             */
/*   Updated: 2025/06/15 15:43:24 by omben-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	print_error_map(char *str)
{
	printf("%s\n", str);
	exit(1);
}

void	check_name(char *name)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	str = ".cub";
	while (name[i])
	{
		if (i != 0 && name[i] == '.' && name[i + 1] != '.')
			break ;
		i++;
	}
	while (str[j])
	{
		if (name[i + j] != str[j])
			print_error_map("1- file invalide");
		j++;
	}
	if (name[i + j])
		print_error_map("2- file invalide");
}

int	check(int ac, char **av)
{
	if (ac != 2)
		print_error_map("number of args invalid");
	check_name(av[1]);
    check_element(av[1]);
	return (1);
}
