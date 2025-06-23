/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omben-ch <omben-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 15:38:56 by omben-ch          #+#    #+#             */
/*   Updated: 2025/06/23 17:28:26 by omben-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	print_error_map(char *str)
{
	ft_putstr_fd(str, 2);
	ft_putstr_fd("\n", 2);
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
	if (ft_strlen(name) < 5)
			print_error_map("1- file invalide");
	while (name[i])
		i++;
	if (name[--i] != 'b' || name[--i] != 'u'|| name[--i] != 'c' || name[--i] != '.')
		print_error_map("2- file invalide");
}

void init_data(t_data *data)
{
    data->n_path = NULL;
    data->w_path = NULL;
    data->e_path = NULL;
    data->s_path = NULL;
    data->c_color = NULL;
    data->f_color = NULL;
    data->map = NULL;
}

void	check(t_data *data, int ac, char **av)
{
	int		fd;

	if (ac != 2)
		print_error_map("number of args invalid");
	check_name(av[1]);
	fd = open(av[1], O_RDONLY);
	if (fd == -1)
		print_error_map(strerror(errno));
	init_data(data);
    get_val_element(data ,fd);
	check_content_fc(data);
	check_content_map(data);
}
