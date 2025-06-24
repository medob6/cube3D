/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omben-ch <omben-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 09:35:56 by omben-ch          #+#    #+#             */
/*   Updated: 2025/06/24 18:08:16 by omben-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	nb_args(char **args)
{
	int	i;

	i = 0;
	while (args && args[i])
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
		print_and_exit("nswe- error extar or no space");
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
			print_and_exit("1- EOF");
		}
		else if (line[0] == '\n')
			free(line);
		else
			return (line);
	}
	return (NULL);
}
