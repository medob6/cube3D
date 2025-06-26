<<<<<<< HEAD
=======
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omben-ch <omben-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 17:12:52 by omben-ch          #+#    #+#             */
/*   Updated: 2025/06/25 16:37:34 by omben-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
>>>>>>> omben-ch

#include "get_next_line.h"

int	read_fails(int n, char **rest)
{
	if (n == -1)
	{
		if (*rest != NULL)
			free(*rest);
		*rest = NULL;
		return (1);
	}
	return (0);
}

char	*checkline_in_rest(char **rest)
{
	int	i;

	i = 0;
	if (*rest)
	{
		while ((*rest)[i] && (*rest)[i] != '\n')
			i++;
		if ((*rest)[i] == '\n')
			return (jbad_line(rest, i, 1));
	}
	return (NULL);
}

char	*proccess_buffer(int fd, char *buf, char **res)
{
<<<<<<< HEAD
	char	*temp;
	int		n;
	int		i;
=======
	free(buffer);
	*line = gnl_ft_strjoin(&line[0][0], &mem[0][0], 10, 1);
	buffer = &mem[0][0];
	*mem = ft_save_for_next(buffer + gnl_ft_strchr(buffer, '\n'));
	free(buffer);
	return (*line);
}
>>>>>>> omben-ch

	n = 1;
	while (n > 0)
	{
<<<<<<< HEAD
		n = read(fd, buf, BUFFER_SIZE);
		if (read_fails(n, res))
			return (NULL);
		buf[n] = '\0';
		temp = *res;
		*res = ft_strjoin(*res, buf);
		free(temp);
		if (!*res)
			return (*res = NULL, NULL);
		i = 0;
		while ((*res)[i] && (*res)[i] != '\n')
			i++;
		if ((*res)[i] == '\n')
			return (jbad_line(res, i, 1));
=======
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
>>>>>>> omben-ch
	}
	return (NULL);
}

char	*get_next_line(int fd)
{
	static char	*rest;
	char		*buf;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
<<<<<<< HEAD
		return (free(rest), NULL);
	buf = malloc(((size_t)BUFFER_SIZE) + 1);
	if (!buf)
		return (free(rest), rest = NULL, NULL);
	line = checkline_in_rest(&rest);
	if (line)
		return (free(buf), line);
	line = proccess_buffer(fd, buf, &rest);
	if (line)
		return (free(buf), line);
	if (line == NULL && (!rest || *rest == '\0'))
		return (free(buf), free(rest), rest = NULL, NULL);
	line = jbad_line(&rest, ft_strlen(rest), 0);
	free(buf);
=======
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
>>>>>>> omben-ch
	return (line);
}
