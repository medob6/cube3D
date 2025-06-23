/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_content_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omben-ch <omben-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 16:57:04 by omben-ch          #+#    #+#             */
/*   Updated: 2025/06/21 16:08:32 by omben-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	counter_line(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (i > 2147483647)
			return (-1);
		i++;
	}
	return ((int)i);
}

int	check_wall_first_last(char *wall)
{
	int	i;

	i = 0;
	while (wall[i])
	{
		if (!ft_strchr("1 ", wall[i]))
			return (1);
		i++;
	}
	return (0);
}

int	check_inside(char *line, int before_last_line)
{
	static int	position;
	int			i;

	i = 0;
	while (line[i] && line[i] == ' ')
	{
		i++;
	}
	if (!ft_strchr("1", line[i]))
		return (1);
	i++;
	while (line[i] && line[i + 1] && line[i + 1] != '\n')
	{
		if (!ft_strchr(" 10NWSE\n", line[i]))
			return (1);
		if (ft_strchr("NWSE", line[i]))
			position++;
		i++;
	}
	while (line[i] && line[i] == ' ')
	{
		i--;
	}
	if (!ft_strchr("1", line[i]) || (position != 1 && before_last_line))
		return (1);
	return (0);
}

int	get_size_of_long_line(t_data *data)
{
	int	i;
	int	size_line;
	int	tmp_size_line;

	i = 0;
	size_line = 0;
	while (data->map[i])
	{
		tmp_size_line = counter_line(data->map[i]);
		if (tmp_size_line == -1)
		{
			printf("line is solong \n");
			exit(1); //! freeing data
		}
		if (tmp_size_line > size_line)
			size_line = tmp_size_line;
		i++;
	}
	return (size_line);
}

void	add_space(t_data *data)
{
	char	*tmp;
	int		size_line;
	int		nb_space;
	int		i;

	i = 0;
	size_line = get_size_of_long_line(data);
	while (data->map[i])
	{
		nb_space = size_line - counter_line(data->map[i]);
		while (nb_space--)
		{
			tmp = data->map[i];
			data->map[i] = ft_strjoin(data->map[i], " ");
			free(tmp);
		}
		i++;
	}
}

void	check_content_map(t_data *data)
{
	int	i;
	int	j;
	int	position;

	i = -1;
	position = 0;
	add_space(data);
	while (data->map[++i])
	{
        j = -1;
        if (check_wall_first_last(data->map[0]) || check_wall_first_last(data->map[nb_args(data->map) - 1]))
        {
			printf("2 - error wall is not valide \n");
			exit(1); //! freeing data
        }
		while (data->map[i][++j])
		{
            if(!ft_strchr(" 10NWSE", data->map[i][j]))
            {
				printf("error wall is not valide \n");
				exit(1); //! freeing data
            }
            if(!ft_strchr(" 10NWSE", data->map[i][j]))
            {
				printf("error wall is not valide \n");
				exit(1); //! freeing data
            }
			if (i && data->map[i][j]&& data->map[i + 1] && ft_strchr("0NWSE", data->map[i][j])
				&& (!ft_strchr("10NWSE", data->map[i][j - 1])
					|| !ft_strchr("10NWSE", data->map[i][j + 1])
					|| !ft_strchr("10NWSE", data->map[i - 1][j])
					|| !ft_strchr("10NWSE", data->map[i + 1][j])))
			{
				printf("error wall is not valide \n");
				exit(1); //! freeing data
			}
			if (ft_strchr("NWSE", data->map[i][j]))
                position++;
		}
	}
    if (position != 1)
    {
		printf("error wall is not valide \n");
		exit(1); //! freeing data
    }
}

// if (i == (size - 2))
//     sign = 1;
// if ((!i && check_wall_first_last(data->map[i])) || ((i == (size - 1))
// 		&& check_wall_first_last(data->map[i])))
//         {
//             printf("error wall is not valide \n");
// 		     exit(1); //! freeing data
//         }
// else if (check_inside(data->map[i], sign))
// {
//     printf("error inside map \n");
// 	exit(1); //! freeing data
// }