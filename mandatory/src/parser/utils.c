/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omben-ch <omben-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 09:35:56 by omben-ch          #+#    #+#             */
/*   Updated: 2025/06/22 16:35:13 by omben-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	nb_args(char **args)
{
	int	i;

	i = 0;
	if (!args)
		print_error_map("1- error malloc");
	while (args[i])
		i++;
	return (i);
}

void	is_only_one_space(char *line)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (line[i])
	{
		if (line[i] == ' ')
			j++;
		i++;
	}
	if (j == 0 || j > 1)
	{
		free(line);
		print_error_map("nswe- error extar or no space");
	}
}

char	*check_newline(int fd)
{
	char	*line;

	while (1)
	{
		line = get_next_line(fd);
		if (!line || !line[0])
		{
			free(line);
			print_error_map("1- EOF");
		}
		else if (line[0] == '\n')
			free(line);
		else
			return (line);
	}
	return (NULL);
}

// void	check_name_of_arg(char *line, char *arg)
// {
// 	char	**args;
// 	int		i;
// 	int		j;

// 	i = 0;
// 	j = 0;
// 	args = ft_split(line, " \t");
// 	if (!args)
// 	{
// 		free(line);
// 		print_error_map("nswe- error malloc");
// 	}
// 	if (nb_args(args) != 2 || args[1][0] == '\n' || args[1][0] == '\0')
// 	{
// 		//! freing list
// 		print_error_map("nswe- more args");
// 	}
// 	if ((args[0][0] == arg[0] && !args[0][1]) || (args[0][0] == arg[0]
// 			&& args[0][1] == arg[1] && !args[0][2]))
//         return ; //! freeing list
//     else
//     {
// 		free(line);
// 		print_error_map("nswe- name invalid");
// 	}
// }
