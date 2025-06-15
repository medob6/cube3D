/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omben-ch <omben-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 17:12:52 by omben-ch          #+#    #+#             */
/*   Updated: 2025/06/15 18:56:19 by omben-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_bzero(void *s, size_t n)
{
	char	*p;

	p = (char *)s;
	while (n-- > 0)
		*(p++) = 0;
	return (1);
}

char	*for_free(char *buffer, char **mem, char *s, int arg)
{
	if (arg == 1)
		free(buffer);
	if (arg == 2)
	{
		free(*mem);
		*mem = NULL;
	}
	if (arg == 3)
		free(s);
	return (NULL);
}

char	*cond_one(char *buffer, char **mem, char **line)
{
	free(buffer);
	*line = gnl_ft_strjoin(&line[0][0], &mem[0][0], 10, 1);
	buffer = &mem[0][0];
	*mem = ft_save_for_next(buffer + gnl_ft_strchr(buffer, '\n'));
	free(buffer);
	return (*line);
}

char	*cond_two(char *buffer, char **mem, char **line)
{
	if (check_return(buffer) > 0)
	{
		*line = gnl_ft_strjoin(&mem[0][0], buffer, 10, 1);
		free((*mem));
		*mem = ft_save_for_next(buffer + gnl_ft_strchr(buffer, '\n'));
		free(buffer);
		return (*line);
	}
	else if (check_return(buffer) < 0)
	{
		if (check_return(&mem[0][0]) == 0)
		{
			*line = ft_save_for_next(&mem[0][0]);
			free(buffer);
			free(*mem);
			*mem = NULL;
			return (*line);
		}
		free(buffer);
		return (NULL);
	}
	return (NULL);
}

char	*get_next_line(int fd)
{
	char		*buffer;
	static char	*mem;
	char		*line;

	line = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (for_free(NULL, &mem, NULL, 2));
	buffer = (char *)malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (for_free(NULL, &mem, NULL, 2));
	if (check_return(mem) > 0)
		return (cond_one(buffer, &mem, &line));
	while (!for_free(NULL, NULL, line, 3) && ft_bzero(buffer, BUFFER_SIZE + 1)
		&& read(fd, buffer, BUFFER_SIZE) > 0 && check_return(buffer) == 0)
	{
		line = mem;
		mem = gnl_ft_strjoin(mem, buffer, 10, 10);
		if (!mem)
			for_free(buffer, NULL, NULL, 1);
	}
	if (check_return(buffer) > 0)
		return (cond_two(buffer, &mem, &line));
	else if (check_return(buffer) < 0)
		return (cond_two(buffer, &mem, &line));
	return (line);
}
