/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omben-ch <omben-ch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 17:12:56 by omben-ch          #+#    #+#             */
/*   Updated: 2025/06/26 17:25:21 by omben-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_gnl_strlen(char *s, int w)
{
	int	i;

	i = 0;
	if (!(s))
		return (0);
	if (w == 1)
	{
		while (s[i] != '\n')
			i++;
		return (i + 1);
	}
	while (s[i])
		i++;
	return (i);
}

int	gnl_ft_strchr(char *s, int c)
{
	int	a;
	int	i;

	a = 0;
	i = ft_gnl_strlen(s, 10);
	while (i >= a)
	{
		if (s[a] == (char)c)
			return (a + 1);
		a++;
	}
	return (0);
}

int	check_return(char *str)
{
	int	i;

	i = 0;
	if (str == NULL || str[0] == '\0')
		return (-1);
	while (str[i] != '\n')
	{
		if (str[i] == '\0')
			return (0);
		i++;
	}
	return (i + 1);
}

char	*ft_save_for_next(char *str)
{
	char	*s;
	int		i;

	i = 0;
	if (str[0] == '\0')
		return (NULL);
	while (str[i])
		i++;
	++i;
	s = (char *)malloc(i);
	if (s == NULL)
		return (NULL);
	i = 0;
	while (str[i])
	{
		s[i] = str[i];
		i++;
	}
	s[i] = '\0';
	return (s);
}

char	*gnl_ft_strjoin(char *s1, char *s2, int s1l, int s2l)
{
	char	*s;
	int		i;

	i = 0;
	s = (char *)malloc((ft_gnl_strlen(s1, s1l) + ft_gnl_strlen(s2, s2l) + 1)
			* sizeof(char));
	if (s == NULL)
		return (NULL);
	if (s1 == NULL)
	{
		while ((*(s2) != '\n') && (*(s2) != '\0'))
			s[i++] = *(s2++);
	}
	else
	{
		while (*(s1))
			s[i++] = *(s1++);
		while ((*(s2) != '\n') && (*(s2) != '\0'))
			s[i++] = *(s2++);
	}
	s[i] = *(s2);
	if (*(s2) == '\n')
		s[++i] = '\0';
	return (s);
}
