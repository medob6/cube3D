/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omben-ch <omben-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/14 15:38:56 by omben-ch          #+#    #+#             */
/*   Updated: 2025/09/15 16:34:41 by omben-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	init_data(t_fcub *fcub)
{
	fcub->n_path = NULL;
	fcub->w_path = NULL;
	fcub->e_path = NULL;
	fcub->s_path = NULL;
	fcub->c_color = NULL;
	fcub->f_color = NULL;
	fcub->map = NULL;
}

void	check_name(char *arg)
{
	int		i;

	i = 0;
	if (ft_strlen(arg) < 5)
		print_error_file_and_exit();
	while (arg[i])
		i++;
	if (arg[--i] != 'b' || arg[--i] != 'u' || arg[--i] != 'c'
		|| arg[--i] != '.')
	{
		if (!ft_strcmp(arg, "--rules"))
		{
			print_cub_rules();
			cleanup(0);
		}
		else
			print_error_file_and_exit();
	}
}

void	parse_and_get_data(t_fcub *fcub, int ac, char **av)
{
	int	fd;

	if (ac != 2)
	{
		print_error_argument("More Arguments");
		cleanup(1);
		cleanup(1);
	}
	check_name(av[1]);
	fd = open(av[1], O_RDONLY);
	if (fd == -1)
		print_and_exit(strerror(errno));
	init_data(fcub);
	get_val_of_element(fcub, fd);
	check_content_fc(fcub);
	check_content_map(fcub);
}
